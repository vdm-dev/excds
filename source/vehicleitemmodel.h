#ifndef VEHICLEITEMMODEL_H
#define VEHICLEITEMMODEL_H


#include <QAbstractItemModel>


class VehicleItemNode;


class VehicleItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit VehicleItemModel(QObject* parent = Q_NULLPTR);

private:
    VehicleItemNode* _rootNode;
};


#endif // VEHICLEITEMMODEL_H
