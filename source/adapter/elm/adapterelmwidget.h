#ifndef ADAPTERELMWIDGET_H
#define ADAPTERELMWIDGET_H


#include "ui_adapterelmwidget.h"


class AdapterElmWidget : public QWidget, private Ui::AdapterElmWidget
{
    Q_OBJECT

public:
    explicit AdapterElmWidget(QWidget* parent = nullptr);

private slots:
    void on__buttonWiFiDefault_clicked();
    void on__buttonUartRefresh_clicked();

private:
    friend class AdapterElm;
};


#endif // ADAPTERELMWIDGET_H
