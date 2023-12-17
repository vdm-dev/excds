#include "adapterelm.h"

#include <QProgressDialog>
#include <QMessageBox>

#include "adapterelmwidget.h"


void AdapterElm::uartCheck()
{
    close();
    open();

    _check = true;

    _progressDialog->setValue(0);
    _progressDialog->setLabelText(tr("Searching for the device"));
}

void AdapterElm::uartTimer()
{
    if (_status == Searching)
    {
        if (_widget->_comboUartPort->currentIndex() < 1) // Port Autodetection
        {
            if (_uartIndex >= _widget->_comboUartPort->count()) // Last Port Iteration
            {
                cancel(tr("The device is not found."));
            }
            else if (_uartIndex == 0) // First Port Iteration
            {
                _baudIndex = 0;

                if (_preferredPort.isEmpty())
                {
                    _uartIndex = 1;
                }
                else
                {
                    for (int i = 0; i < _widget->_comboUartPort->count(); ++i)
                    {
                        if (_widget->_comboUartPort->itemData(i) == _preferredPort)
                        {
                            _uartIndex = -1;
                            break;
                        }
                    }
                }
            }
            else // Middle Port Iteration
            {
                if (_uartIndex < 0) // Preferred Port Iteration
                {
                    uartCheckPort(_preferredPort);
                }
                else // Regular Port Iteration
                {
                    QString portName = _widget->_comboUartPort->itemData(_uartIndex).toString();

                    if (portName == _preferredPort) // Skip Preferred Port Iteration
                    {
                        _uartIndex++;
                        _baudIndex = 0;
                    }
                    else
                    {
                        uartCheckPort(portName);
                    }
                }
            }
        }
        else // Fixed Port
        {
            if (_uartIndex == 0) // First (and only) Fixed Port Iteration
            {
                uartCheckPort(_widget->_comboUartPort->currentData().toString());
            }
            else // Last Fixed Port Iteration
            {
                cancel(tr("The device is not found."));
            }
        }
    }
    else if (_status == Connected)
    {
        if (_timeout.elapsed() >= TimeoutData)
        {
            qDebug() << "Timeout";

            _uart.close();

            setStatus(Searching);
        }
    }
}

void AdapterElm::uartCheckPort(const QString& portName)
{
    int baudrate = 0;

    if (_widget->_comboUartBaud->currentIndex() < 1) // Baud Autodetection
    {
        if (_baudIndex == 0 && _preferredBaud > 0) // Preferred Baud Iteration
            baudrate = _preferredBaud;

        _baudIndex++;

        if (baudrate == 0)
        {
            if (_baudIndex >= _widget->_comboUartBaud->count()) // Last Baud Iteration
            {
                _uartIndex = (_uartIndex < 0) ? 1 : (_uartIndex + 1);
                _baudIndex = 0;
                return;
            }
            else // Middle Baud Iteration
            {
                baudrate = _widget->_comboUartBaud->itemData(_baudIndex).toInt();

                if (baudrate == 0 || baudrate == _preferredBaud)
                    return;
            }
        }
    }
    else // Fixed Baudrate
    {
        if (_baudIndex == 0) // First (and only) Fixed Baud Iteration
        {
            baudrate = _widget->_comboUartBaud->currentData().toInt();
            _baudIndex = 1;
        }
        else // Last Fixed Baud Iteration
        {
            _uartIndex = (_uartIndex < 0) ? 1 : (_uartIndex + 1);
            _baudIndex = 0;
            return;
        }
    }

    _progressDialog->setValue(_uartIteration * 100 / _uartTotal);
    _progressDialog->setLabelText(tr("Searching for the device at port %1 (%2 bps)")
        .arg(portName).arg(baudrate));

    _uartIteration++;

    _uart.setPortName(portName);
    _uart.setBaudRate(baudrate);

    if (_uart.open(QSerialPort::ReadWrite))
    {
        _buffer.clear();

        setStatus(Connected);
        sendCommand("I");
    }
}
