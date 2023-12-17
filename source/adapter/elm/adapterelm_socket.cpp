#include "adapterelm.h"

#include <QProgressDialog>
#include <QMessageBox>

#include "adapterelmwidget.h"


void AdapterElm::socketCheck()
{
    close();
    open();

    _check = true;

    _progressDialog->setValue(0);
    _progressDialog->setLabelText(tr("Connecting to %1:%2")
        .arg(_socketAddress.toString()).arg(_socketPort));
}

void AdapterElm::socketConnected()
{
    if (_check)
    {
        _progressDialog->setValue(50);
        _progressDialog->setLabelText(tr("The device is successfully connected"));
    }

    _buffer.clear();

    setStatus(Connected);
    sendCommand("I");
}

void AdapterElm::socketDisconnected()
{
    cancel(tr("The connection was closed by a remote host."));
}

void AdapterElm::socketError(QAbstractSocket::SocketError error)
{
    cancel(tr("The connection was not established due to a network error (code: %1).").arg(error));
}

void AdapterElm::socketTimer()
{
    if (_status == Connecting)
    {
        if (_socket.state() != QAbstractSocket::ConnectedState)
        {
            if (_timeout.elapsed() >= TimeoutConnect)
            {
                cancel(tr("The connection has not been established in the allotted time."));
            }
            else if (_check)
            {
                _progressDialog->setValue(
                    (static_cast<int>(_timeout.elapsed()) * 50) / TimeoutConnect);
                _progressDialog->setLabelText(tr("Connecting to %1:%2")
                    .arg(_socketAddress.toString()).arg(_socketPort));
            }
        }
    }
    else if (_status == Connected)
    {
        if (_timeout.elapsed() >= TimeoutData)
        {
            cancel(tr("The device did not respond in time."));
        }
        else if (_check)
        {
            _progressDialog->setValue(
                (static_cast<int>(_timeout.elapsed()) * 50) / TimeoutData + 50);
            _progressDialog->setLabelText(tr("Waiting for a response from the device"));
        }
    }
}
