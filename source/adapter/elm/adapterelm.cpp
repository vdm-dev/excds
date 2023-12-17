#include "adapterelm.h"

#include <QDebug>
#include <QProgressDialog>
#include <QProgressBar>
#include <QMessageBox>

#include "adapterelmwidget.h"


AdapterElm::AdapterElm(QObject* parent)
    : IAdapter(parent)
    , _status(Disconnected)
    , _preferredBaud(0)
    , _check(false)
{
    _widget = new AdapterElmWidget();

    QProgressBar* progressBar = new QProgressBar();
    progressBar->setTextVisible(false);

    QLabel* progresslabel = new QLabel();
    progresslabel->setWordWrap(true);
    progresslabel->setAlignment(Qt::AlignCenter);

    QFont progressLabelFont = progresslabel->font();
    progressLabelFont.setBold(true);
    progresslabel->setFont(progressLabelFont);

    _progressDialog = new QProgressDialog(_widget);
    Qt::WindowFlags flags = _progressDialog->windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    _progressDialog->setWindowFlags(flags);
    _progressDialog->setBar(progressBar);
    _progressDialog->setLabel(progresslabel);
    _progressDialog->setRange(0, 100);
    _progressDialog->setWindowModality(Qt::WindowModal);
    _progressDialog->setMinimumDuration(0);
    _progressDialog->reset();

    int progressWidth = _widget->width() / 2;
    if (progressWidth > 400)
        progressWidth = 400;

    _progressDialog->setFixedWidth(progressWidth);

    _uart.setDataBits(QSerialPort::Data8);
    _uart.setFlowControl(QSerialPort::NoFlowControl);
    _uart.setParity(QSerialPort::NoParity);
    _uart.setStopBits(QSerialPort::OneStop);

    connect(&_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(&_socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(&_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
        SLOT(socketError(QAbstractSocket::SocketError)));

    connect(&_uart, SIGNAL(readyRead()), this, SLOT(readyRead()));

    connect(_widget->_buttonWiFiCheck, SIGNAL(clicked()), this, SLOT(socketCheck()));
    connect(_widget->_buttonUartCheck, SIGNAL(clicked()), this, SLOT(uartCheck()));

    connect(_progressDialog, SIGNAL(canceled()), this, SLOT(cancel()));
}

bool AdapterElm::open()
{
    if (!_widget || isOpen())
        return false;

    _buffer.clear();

    if (_widget->_radioWiFi->isChecked())
    {
        _socketAddress.setAddress(_widget->_editWiFiAddress->text());
        _socketPort = _widget->_editWiFiPort->value();

        _socket.connectToHost(_socketAddress, static_cast<quint16>(_socketPort));

        setStatus(Connecting);

        connect(&_timer, SIGNAL(timeout()), this, SLOT(socketTimer()));

        _timer.start(TimeoutCheckSocket);
        _timeout.start();
    }
    else if (_widget->_radioUart->isChecked())
    {
        _uartIndex = 0;
        _uartIteration = 0;
        _baudIndex = 0;

        // Port Autodetection
        if (_widget->_comboUartPort->currentIndex() < 1)
        {
            _widget->on__buttonUartRefresh_clicked();
            _uartTotal = _widget->_comboUartPort->count() - 1;
        }
        else
        {
            _uartTotal = 1;
        }

        // Baud Autodetection
        if (_widget->_comboUartBaud->currentIndex() < 1)
            _uartTotal *= _widget->_comboUartBaud->count() - 1;

        connect(&_timer, SIGNAL(timeout()), this, SLOT(uartTimer()));

        setStatus(Searching);
        _timer.start(TimeoutCheckUart);
    }
    else
    {
        return false;
    }

    return true;
}

void AdapterElm::close()
{
    disconnect(&_timer, SIGNAL(timeout()), Q_NULLPTR, Q_NULLPTR);

    _timer.stop();
    _socket.abort();

    if (_uart.isOpen())
        _uart.close();

    _buffer.clear();
    _check = false;

    _stage = StageNone;

    setStatus(Disconnected);
}

void AdapterElm::reconfigure()
{
    sendCommand("D");
    _stage = StageConfiguringReset;
}

bool AdapterElm::isOpen() const
{
    return _socket.state() != QAbstractSocket::UnconnectedState || _uart.isOpen();
}

QIcon AdapterElm::icon() const
{
    return _widget->windowIcon();
}

QString AdapterElm::name() const
{
    return _widget->windowTitle();
}

QWidget* AdapterElm::widget()
{
    return _widget;
}

void AdapterElm::readyRead()
{
    QByteArray data;

    if (_uart.isOpen())
    {
        data = _uart.readAll();
    }
    else if (_socket.state() == QAbstractSocket::ConnectedState)
    {
        data = _socket.readAll();
    }

    for (int i = 0; i < data.size(); ++i)
    {
        if (data[i] == '\0' || data[i] == '\n')
        {
            continue;
        }
        else if (data[i] == '>')
        {
            processAnswer(_buffer.split('\r', QString::SkipEmptyParts));
            _buffer.clear();
            break;
        }
        else
        {
            _buffer += data[i];
        }
    }
}

void AdapterElm::cancel()
{
    _progressDialog->reset();

    _socket.blockSignals(true);
    close();
    _socket.blockSignals(false);
}

void AdapterElm::cancel(const QString& message, bool error)
{
    if (!_check)
        return;

    cancel();

    if (error)
    {
        QMessageBox::critical(_widget, tr("Connection failed"), message,
            QMessageBox::Close, QMessageBox::Close);
    }
    else
    {
        QMessageBox::information(_widget, tr("Connection established"), message,
            QMessageBox::Ok, QMessageBox::Ok);
    }
}

void AdapterElm::processAnswer(const QStringList& lines)
{
    qDebug() << lines;

    if (_status == Connected) // That means the device is *JUST* connected
    {
        for (int i = 0; i < lines.size(); ++i)
        {
            if (lines[i].startsWith("ELM327"))
            {
                if (_uart.isOpen())
                {
                    _preferredPort = _uart.portName();
                    _preferredBaud = _uart.baudRate();
                }

                //if (!_check)
                {
                    setStatus(Active);
                    reconfigure();
                }

                //cancel(tr("The device is found and ready to go.<br><br>"
                //          "Device information:<br><i>%1</i>").arg(lines[i]), false);

                return;
            }
        }

        return;
    }

    // The Device is Active
    switch (_stage)
    {
    case StageConfiguringReset:
        sendCommand(_configuration.echo ? "E1" : "E0");
        _stage = StageConfiguringEcho;
        break;

    case StageConfiguringEcho:
        sendCommand(_configuration.spaces ? "S1" : "S0");
        _stage = StageConfiguringSpaces;
        break;

    case StageConfiguringSpaces:
        sendCommand(_configuration.headers ? "H1" : "H0");
        _stage = StageConfiguringHeaders;
        break;

    default:
        break;
    }
}

void AdapterElm::sendCommand(const QString& command)
{
    QByteArray data("AT");
    data.append(command.toLatin1());
    data.append('\r');

    if (_uart.isOpen())
    {
        _uart.write(data);
    }
    else if (_socket.state() == QAbstractSocket::ConnectedState)
    {
        _socket.write(data);
    }
    else
    {
        return;
    }

    _stage = StageCommand;
    _timeout.start();
}

void AdapterElm::setStatus(AdapterElm::Status value)
{
    _status = value;
}
