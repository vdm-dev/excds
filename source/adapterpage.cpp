#include "adapterpage.h"

#include <QDebug>

#include <iadapter.h>

#include "adapter/elm/adapterelm.h"
#include "adapterlistitemdelegate.h"


AdapterPage::AdapterPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi(this);

    _list->setItemDelegate(new AdapterListItemDelegate());

    _adapters << (new AdapterElm());

    for (int i = 0; i < _adapters.size(); ++i)
    {
        QListWidgetItem* item = new QListWidgetItem(_adapters[i]->icon(), _adapters[i]->name());
        item->setData(Qt::UserRole, i);

        _list->addItem(item);

        if (_adapters[i]->widget())
            _pages->addWidget(_adapters[i]->widget());
    }

    //int hintHeight = _list->sizeHintForRow(0);
    //_list->setMinimumHeight(hintHeight + hintHeight / 2 + hintHeight / 4);
}

IAdapter* AdapterPage::currentAdapter()
{
    QListWidgetItem* item = _list->currentItem();

    if (!item)
        return nullptr;

    bool ok;
    int index = item->data(Qt::UserRole).toInt(&ok);

    if (!ok || index < 0 || index >= _adapters.size())
        return nullptr;

    return _adapters.at(index);
}

void AdapterPage::on__list_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(previous)

    if (!current)
    {
        _pages->setCurrentWidget(_pageEmpty);
        return;
    }

    bool ok;
    int index = current->data(Qt::UserRole).toInt(&ok);

    if (!ok || index < 0 || index >= _adapters.size())
    {
        _pages->setCurrentWidget(_pageEmpty);
        return;
    }

    IAdapter* adapter = _adapters.at(index);

    if (!adapter)
    {
        _pages->setCurrentWidget(_pageEmpty);
        return;
    }

    QWidget* widget = adapter->widget();

    _pages->setCurrentWidget(widget ? widget : _pageEmpty);
}
