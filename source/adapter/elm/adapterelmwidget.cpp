#include "adapterelmwidget.h"

#include <algorithm>

#include <QSerialPortInfo>


bool compareQSerialPortInfo(const QSerialPortInfo& first, const QSerialPortInfo& second)
{
    if (first.portName().size() == second.portName().size())
    {
        return first.portName() > second.portName();
    }
    else
    {
        return first.portName().size() > second.portName().size();
    }
}


AdapterElmWidget::AdapterElmWidget(QWidget* parent)
    : QWidget(parent)
{
    setupUi(this);

    _comboUartBaud->addItem(tr("Autodetection"));
    _comboUartBaud->addItem(tr("115 200"), 115200);
    _comboUartBaud->addItem(tr("57 600"), 57600);
    _comboUartBaud->addItem(tr("38 400 (default)"), 38400);
    _comboUartBaud->addItem(tr("9 600"), 9600);
    _comboUartBaud->setCurrentIndex(0);

    on__buttonWiFiDefault_clicked();
    on__buttonUartRefresh_clicked();

    _radioWiFi->setChecked(true);
}

void AdapterElmWidget::on__buttonWiFiDefault_clicked()
{
    _editWiFiAddress->setText("192.168.0.10");
    _editWiFiPort->setValue(35000);
}

void AdapterElmWidget::on__buttonUartRefresh_clicked()
{
    QString portName = _comboUartPort->currentData().toString();

    _comboUartPort->clear();
    _comboUartPort->addItem(tr("Autodetection"));

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    std::sort(ports.begin(), ports.end(), compareQSerialPortInfo);

    int index = 0;

    for (int i = 0; i < ports.size(); ++i)
    {
        _comboUartPort->addItem(ports[i].portName(), ports[i].portName());

        if (ports[i].portName() == portName)
            index = i + 1;
    }

    if (index < 1 && !portName.isEmpty())
    {
        _comboUartPort->addItem(portName + tr(" (unavailable)"), portName);
        index = _comboUartPort->count() - 1;
    }

    _comboUartPort->setCurrentIndex(index);
}
