QT       += webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = dcmapkit
TEMPLATE = lib

DEFINES += DCMAPKIT_LIBRARY

DESTDIR = ../lib
OBJECTS_DIR = ../build
MOC_DIR = ../build
RCC_DIR = ../build
UI_DIR = ../build

SOURCES += \
    dcCoordinate.cpp \
    dcCoordinateRegion.cpp \
    dcCoordinateSpan.cpp \
    dcMapView.cpp

HEADERS +=\
    dcCoordinate.h \
    dcMapglobal.h \
    dcMapKit.h \
    dcMapView.h \
    dcCoordinateSpan.h \
    dcCoordinateRegion.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    dcmapkit_resources.qrc

OTHER_FILES += \
    gmap.html \
    gmap.js
