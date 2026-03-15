#include "vehiclepage.h"

#include <QItemSelectionModel>

#include "adapterlistitemdelegate.h"
#include "vehicleitemmodel.h"


VehiclePage::VehiclePage(QWidget* parent)
    : QWidget(parent)
{
    setupUi(this);

    VehicleItemModel* model = new VehicleItemModel(this);
    model->load(":/data/vehicles.xml");

    _list->setModel(model);
    _list->setItemDelegate(new AdapterListItemDelegate());

    _comboModel->setModel(model);
    _comboGeneration->setModel(model);
    _comboEcu->setModel(model);

    auto currentChanged = &QItemSelectionModel::currentChanged;
    connect(_list->selectionModel(), currentChanged, this, &VehiclePage::brandChanged);

    auto currentIndexChanged = QOverload<int>::of(&QComboBox::currentIndexChanged);
    connect(_comboModel, currentIndexChanged, this, &VehiclePage::modelChanged);
    connect(_comboGeneration, currentIndexChanged, this, &VehiclePage::generationChanged);
}

void VehiclePage::brandChanged(const QModelIndex& current, const QModelIndex&)
{
    _comboModel->setRootModelIndex(current);
    _comboModel->setCurrentIndex(0);
}

void VehiclePage::modelChanged(int index)
{
    auto parentIndex = _comboModel->rootModelIndex();
    if (!parentIndex.isValid())
        return;

    auto model = parentIndex.model();
    _comboGeneration->setRootModelIndex(model->index(index, 0, parentIndex));
    _comboGeneration->setCurrentIndex(0);
}

void VehiclePage::generationChanged(int index)
{
    auto parentIndex = _comboGeneration->rootModelIndex();
    if (!parentIndex.isValid())
        return;

    auto model = parentIndex.model();
    _comboEcu->setRootModelIndex(model->index(index, 0, parentIndex));
    _comboEcu->setCurrentIndex(0);
}
