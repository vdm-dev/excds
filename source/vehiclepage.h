#ifndef VEHICLEPAGE_H
#define VEHICLEPAGE_H


#include "ui_vehiclepage.h"


class VehiclePage : public QWidget, private Ui::VehiclePage
{
    Q_OBJECT

public:
    explicit VehiclePage(QWidget* parent = nullptr);

private slots:
    void brandChanged(const QModelIndex& current, const QModelIndex& previous);
    void modelChanged(int index);
    void generationChanged(int index);
};


#endif // VEHICLEPAGE_H
