TEMPLATE = lib
CONFIG += qt plugin resources
QT += declarative script

TARGET = cometdplugin

DESTDIR = ../Cometd

HEADERS += \
    cometdplugin.h \
    cometd.h \
    timerwindow.h

SOURCES += \
    cometdplugin.cpp \
    cometd.cpp \
    timerwindow.cpp

RESOURCES += \
    src.qrc

OTHER_FILES += \
    3rdparty/cometd/cometd-javascript/common/src/main/js/org/cometd/* \
    cometd.qml \
    cometd_p.js

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
