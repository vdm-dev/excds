#ifndef BRANDITEMMODEL_H
#define BRANDITEMMODEL_H


#include <QAbstractListModel>


class BrandItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    BrandItemModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
};


#endif // BRANDITEMMODEL_H
