#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <fancymainwindow.h>


class QAction;

namespace Manhattan
{
class FancyTabWidget;
}

class HeaderBar;
class AdapterPage;
class VehiclePage;
class DtcPage;
class LiveDataPage;

class MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void currentTabChanged(int index);

private:
    QAction* _actionStart;

    Manhattan::FancyTabWidget* _tabs;

    HeaderBar* _headerBar;

    AdapterPage*  _pageAdapter;
    VehiclePage*  _pageVehicle;
    DtcPage*      _pageDtc;
    LiveDataPage* _pageLiveData;

    void setupUi();
};


#endif // MAINWINDOW_H
