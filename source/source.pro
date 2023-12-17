PROJECT_ROOT = $${PWD}/..

QT += core gui widgets network serialport

TARGET = excds
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $${OUT_PWD}/../bin

CONFIG += c++11
CONFIG += file_copies

INCLUDEPATH += $${PWD} $${PROJECT_ROOT}/dependencies/qt-manhattan-style

LIBS += -L$${OUT_PWD}/../lib -lqt-manhattan-style

COPIES += libraries

libraries.files = $$files($${OUT_PWD}/../lib/*.dll)
libraries.path = $${OUT_PWD}/../bin

SOURCES += \
    adapter/elm/adapterelm.cpp \
    adapter/elm/adapterelm_socket.cpp \
    adapter/elm/adapterelm_uart.cpp \
    adapter/elm/adapterelmwidget.cpp \
    adapterlistitemdelegate.cpp \
    adapterpage.cpp \
    dtcpage.cpp \
    livedatapage.cpp \
    main.cpp \
    mainwindow.cpp \
    headerbar.cpp \
    vehicleitemmodel.cpp \
    vehicleitemnode.cpp \
    vehiclepage.cpp \
    branditemmodel.cpp \
    simpleecudatabase.cpp

HEADERS += \
    adapter/elm/adapterelm.h \
    adapter/elm/adapterelmwidget.h \
    adapterpage.h \
    dtcpage.h \
    livedatapage.h \
    mainwindow.h \
    headerbar.h \
    vehicleitemmodel.h \
    vehicleitemnode.h \
    vehiclepage.h \
    iadapter.h \
    branditemmodel.h \
    iecudatabase.h \
    simpleecudatabase.h

RESOURCES += \
    source.qrc

FORMS += \
    adapter/elm/adapterelmwidget.ui \
    adapterpage.ui \
    dtcpage.ui \
    livedatapage.ui \
    vehiclepage.ui \
