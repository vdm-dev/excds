#include "adapterlistitemdelegate.h"

#include <QDebug>


AdapterListItemDelegate::AdapterListItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}

void AdapterListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
        const QModelIndex& index) const
{
    QStyleOptionViewItem newOption = option;

    newOption.font.setBold(newOption.state & QStyle::State_Selected);
    newOption.showDecorationSelected = true;
    newOption.viewItemPosition = QStyleOptionViewItem::OnlyOne;

    QStyledItemDelegate::paint(painter, newOption, index);
}

QSize AdapterListItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);

    result.setWidth(result.width() + 20);
    result.setHeight(result.height() + 10);

    return result;
}
