TEMPLATE = lib
CONFIG += qt plugin resources
QT += declarative script

MODULE_NAME = Cometd
MODULE_DIR = $$OUT_PWD/../$${MODULE_NAME}

TARGET = cometdplugin
DESTDIR = $$MODULE_DIR/private

HEADERS += \
    timerwindow.h \
    cometdplugin.h \
    cometd.h \
    binding.h

SOURCES += \
    cometdplugin.cpp \
    timerwindow.cpp \
    cometd.cpp \
    binding.cpp

RESOURCES += \
    src.qrc

OTHER_FILES += \
    api/Cometd.qml \
    3rdparty/cometd/cometd-javascript/common/src/main/js/org/cometd/* \
    cometd.qml \
    cometd.js

api.target = api
api.commands = $$QMAKE_COPY $$PWD/api/Cometd.qml $$MODULE_DIR
QMAKE_EXTRA_TARGETS += api
PRE_TARGETDEPS += api

qmldir.target = qmldir
qmldir.commands = \
    echo plugin $$TARGET > $$DESTDIR/qmldir && \
    echo Cometd 1.0 Cometd.qml > $$MODULE_DIR/qmldir

QMAKE_EXTRA_TARGETS += qmldir
PRE_TARGETDEPS += qmldir
