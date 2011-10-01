TEMPLATE = lib
CONFIG += qt plugin resources
QT += declarative script

TARGET = cometdplugin

DESTDIR = $$OUT_PWD/../Cometd/private

HEADERS += \
    timerwindow.h \
    cometdplugin.h \
    cometd.h

SOURCES += \
    cometdplugin.cpp \
    timerwindow.cpp \
    cometd.cpp

RESOURCES += \
    src.qrc

OTHER_FILES += \
    3rdparty/cometd/cometd-javascript/common/src/main/js/org/cometd/* \
    cometd.qml \
    cometd.js
