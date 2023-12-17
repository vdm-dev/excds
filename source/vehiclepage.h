#ifndef VEHICLEPAGE_H
#define VEHICLEPAGE_H

#include "ui_vehiclepage.h"

class VehiclePage : public QWidget, private Ui::VehiclePage
{
    Q_OBJECT

public:
    explicit VehiclePage(QWidget* parent = nullptr);
};

#endif // VEHICLEPAGE_H
