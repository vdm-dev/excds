#include "vehicleitemmodel.h"

#include "vehicleitemnode.h"


VehicleItemModel::VehicleItemModel(QObject* parent)
    : QAbstractItemModel(parent)
    , _rootNode(Q_NULLPTR)
{

}
