QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets network

TARGET = demo
TEMPLATE = app

INCLUDEPATH += ../DcMapLib
LIBS += -L../lib -ldcmapkit

SOURCES += main.cpp\
    gpsReceiver.cpp \
    mainWidget.cpp \
    proxySetting.cpp

HEADERS  += \
    gpsReceiver.h \
    mainWidget.h \
    proxySetting.h
