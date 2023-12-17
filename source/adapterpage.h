#ifndef ADAPTERPAGE_H
#define ADAPTERPAGE_H


#include "ui_adapterpage.h"

#include <QList>


class IAdapter;


class AdapterPage : public QWidget, private Ui::AdapterPage
{
    Q_OBJECT

public:
    explicit AdapterPage(QWidget* parent = nullptr);

    IAdapter* currentAdapter();

private slots:
    void on__list_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

private:
    QList<IAdapter*> _adapters;
};


#endif // ADAPTERPAGE_H
