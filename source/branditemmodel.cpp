#include "branditemmodel.h"


BrandItemModel::BrandItemModel(QObject* parent)
    : QAbstractListModel(parent)
{

}

int BrandItemModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int BrandItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return 2;
}

QVariant BrandItemModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
        return tr("Test");

    return QVariant();
}
