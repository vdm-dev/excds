#ifndef DTCPAGE_H
#define DTCPAGE_H

#include "ui_dtcpage.h"

class DtcPage : public QWidget, private Ui::DtcPage
{
    Q_OBJECT

public:
    explicit DtcPage(QWidget* parent = nullptr);
};

#endif // DTCPAGE_H
