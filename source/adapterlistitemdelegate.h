#ifndef ADAPTERLISTITEMDELEGATE_H
#define ADAPTERLISTITEMDELEGATE_H


#include <QStyledItemDelegate>


class AdapterListItemDelegate : public QStyledItemDelegate
{
public:
    AdapterListItemDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem& option,
        const QModelIndex& index) const;
};


#endif // ADAPTERLISTITEMDELEGATE_H
