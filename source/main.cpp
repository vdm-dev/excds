#include <QApplication>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    application.setApplicationName("EXCDS");
    application.setApplicationVersion("1.0");

    //application.setOrganizationName("EXCDS Software");
    //application.setOrganizationDomain("excds.ru");

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
