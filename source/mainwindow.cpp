#include "mainwindow.h"

#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QLabel>
#include <QFont>
#include <QFontMetrics>
#include <QStatusBar>
#include <QAction>

#include <manhattanstyle.h>
#include <fancytabwidget.h>
#include <fancyactionbar.h>
#include <stylehelper.h>
#include <styledbar.h>

#include "headerbar.h"
#include "adapterpage.h"
#include "vehiclepage.h"
#include "dtcpage.h"
#include "livedatapage.h"


MainWindow::MainWindow(QWidget* parent)
    : Manhattan::FancyMainWindow(parent)
{
    setupUi();

    connect(_tabs, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));

    _tabs->setCurrentIndex(0);
}

void MainWindow::currentTabChanged(int index)
{
    QWidget* widget = _tabs->widget(index);

    if (widget)
    {
        _headerBar->setText(widget->windowTitle());
    }
    else
    {
        _headerBar->setText(QString());
    }
}

void MainWindow::setupUi()
{
    using Manhattan::FancyActionBar;

    if (objectName().isEmpty())
        setObjectName(QString("MainWindow"));

    resize(800, 550);
    setMinimumSize(800, 550);

    QString styleName = QApplication::style()->objectName();

#if !defined (Q_OS_WIN) && !defined (Q_OS_DARWIN)
    if (styleName == QLatin1String("windows"))
        styleName = QLatin1String("fusion");
#endif

    const QStringList styles = QStyleFactory::keys();

    if (styles.contains(QLatin1String("fusion"), Qt::CaseInsensitive))
        styleName = QLatin1String("fusion");

    ManhattanStyle* style = new ManhattanStyle(styleName);
    //QApplication::setStyle(style);

    _headerBar = new HeaderBar();
    _pageAdapter = new AdapterPage();
    _pageVehicle = new VehiclePage();
    _pageDtc = new DtcPage();
    _pageLiveData = new LiveDataPage();

    QIcon icon;
    icon.addFile(QString(":/images/button_start_normal.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon.addFile(QString(":/images/button_start_disabled.png"), QSize(), QIcon::Disabled, QIcon::Off);

    _actionStart = new QAction(icon, tr("Start/Stop"), Q_NULLPTR);
    _actionStart->setProperty("titledAction", true);
    _actionStart->setProperty("subtitle", tr("Start"));

    QAction* action = new QAction(tr("ECU Status"), Q_NULLPTR);
    action->setProperty("titledAction", true);
    action->setProperty("heading", tr("ECU Status"));

    FancyActionBar* actionBar = new FancyActionBar();
    actionBar->setSeparator(FancyActionBar::None);
    actionBar->insertAction(0, _actionStart);
    actionBar->insertAction(1, action);


    _tabs = new Manhattan::FancyTabWidget(this);
    _tabs->setStyle(style);
    //_tabs->statusBar()->setStyle(style);
    //_tabs->setStyledBarHidden(true);
    _tabs->setHeaderBar(_headerBar);
    _tabs->addBottomCornerWidget(actionBar);

    _tabs->insertTab(0, _pageAdapter, _pageAdapter->windowIcon(), _pageAdapter->windowTitle());
    _tabs->insertTab(1, _pageVehicle, _pageVehicle->windowIcon(), _pageVehicle->windowTitle());
    _tabs->insertTab(2, _pageDtc, _pageDtc->windowIcon(), _pageDtc->windowTitle());
    _tabs->insertTab(3, _pageLiveData, _pageLiveData->windowIcon(), _pageLiveData->windowTitle());

    _tabs->setTabEnabled(0, true);
    _tabs->setTabEnabled(1, true);
    _tabs->setTabEnabled(2, true);
    _tabs->setTabEnabled(3, true);


    setCentralWidget(_tabs);

    Manhattan::Utils::StyleHelper::setBaseColor(
                QColor(Manhattan::Utils::StyleHelper::DEFAULT_BASE_COLOR));
}
