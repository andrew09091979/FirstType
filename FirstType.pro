#-------------------------------------------------
#
# Project created by QtCreator 2013-01-28T13:36:13
#
#-------------------------------------------------

QT       += core gui

TARGET = FirstType
TEMPLATE = app
win32: INCLUDEPATH += "C:\\Installers\\Loki\\loki-0.1.7\\include\\"
win32: INCLUDEPATH += "C:\\installers\\boost\\boost_1_51_0\\"
unix: INCLUDEPATH += "/home/andrew/Qt5.0.2/5.0.2/gcc/include"
SOURCES += main.cpp\
        mainwindow.cpp \
    devwnd.cpp \
    syncronizer.cpp \
    chanwidget.cpp \
    chanwidgetlcd.cpp \
    chanwidgetled.cpp \
    connectionImplQT.cpp \
    connectionImplBoost.cpp \
    chanwidgetmanometer.cpp \
    deviceImitator.cpp \
    deviceImitator10007.cpp \
    connectionImplRandomStub.cpp \
    enteringaddress.cpp

HEADERS  += mainwindow.h \
    devwnd.h \
    device.h \
    deviceholder.h \
    protocol.h \
    syncronizer.h \
    syncronizeable.h \
    chanwidgetcreator.h \
    chanwidget.h \
    ProtocolImpl.h \
    protocolimplboost.h \
    chanwidgetlcd.h \
    chanwidgetled.h \
    connectionImplRandomStub.h \
    protocolCallback.h \
    protocol10007.h \
    deviceCallback.h \
    connectionImplQT.h \
    connectionImplBoost.h \
    connectionImpl.h \
    connectionCallback.h \
    chanwidgetmanometer.h \
    wrapped.h \
    deviceImitator.h \
    deviceImitator10007.h \
    enteringaddress.h

FORMS    += mainwindow.ui \
    enteringaddress.ui

QMAKE_CXXFLAGS += -std=c++0x

unix:!macx:!symbian: LIBS += -lboost_system
QT += network

win32: LIBS += -llibboost_system-vc100-mt-gd-1_51
