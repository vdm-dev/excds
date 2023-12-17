#include "vehiclepage.h"

#include "adapterlistitemdelegate.h"
#include "branditemmodel.h"


VehiclePage::VehiclePage(QWidget* parent)
    : QWidget(parent)
{
    setupUi(this);


    BrandItemModel* model = new BrandItemModel();
    _list->setModel(model);
    _list->setItemDelegate(new AdapterListItemDelegate());
}
