#ifndef LIVEDATAPAGE_H
#define LIVEDATAPAGE_H

#include "ui_livedatapage.h"

class LiveDataPage : public QWidget, private Ui::LiveDataPage
{
    Q_OBJECT

public:
    explicit LiveDataPage(QWidget* parent = nullptr);
};

#endif // LIVEDATAPAGE_H
