#ifndef ADAPTERELM_H
#define ADAPTERELM_H


#include <iadapter.h>

#include <QTimer>
#include <QElapsedTimer>
#include <QTcpSocket>
#include <QSerialPort>
#include <QHostAddress>
#include <QStringList>


class QProgressDialog;

class AdapterElmWidget;


class AdapterElmConfiguration
{
public:
    AdapterElmConfiguration()
        : echo(true)
        , spaces(false)
        , headers(true)
    {
    }

    bool echo;
    bool spaces;
    bool headers;
};


class AdapterElm : public IAdapter
{
    Q_OBJECT

public:
    enum Status
    {
        Disconnected,
        Searching,
        Connecting,
        Connected,
        Active
    };

    AdapterElm(QObject* parent = nullptr);

    virtual bool open();
    virtual void close();

    virtual void reconfigure();

    virtual bool isOpen() const;

    virtual QIcon icon() const;
    virtual QString name() const;

    virtual QWidget *widget();

private slots:
    void readyRead();
    void cancel();
    void cancel(const QString& message, bool error = true);

    // Socket Slots
    void socketCheck();
    void socketConnected();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError error);
    void socketTimer();

    // UART Slots
    void uartCheck();
    void uartTimer();

private:
    enum
    {
        TimeoutCheckSocket = 200,
        TimeoutCheckUart = 200,
        TimeoutConnect = 10000,
        TimeoutData = 1000
    };

    enum
    {
        StageNone,
        StageCommand,
        StageData,
        StageConfiguringReset,
        StageConfiguringEcho,
        StageConfiguringSpaces,
        StageConfiguringHeaders,
        StageConfiguringProtocol
    };

    void processAnswer(const QStringList& lines);
    void sendCommand(const QString& command);
    void setStatus(Status value);

    // UART Private Functions
    void uartCheckPort(const QString& portName);

    QTimer _timer;
    QElapsedTimer _timeout;
    QTcpSocket _socket;
    QSerialPort _uart;
    QHostAddress _socketAddress;
    QString _buffer;
    QString _preferredPort;

    QProgressDialog* _progressDialog;

    AdapterElmWidget* _widget;

    AdapterElmConfiguration _configuration;

    Status _status;

    int _socketPort;
    int _uartIndex;
    int _uartIteration;
    int _uartTotal;
    int _baudIndex;
    int _preferredBaud;
    int _stage;

    bool _check;
};


#endif // ADAPTERELM_H
