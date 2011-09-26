#include "cometd.h"

#include "timerwindow.h"

#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>

Cometd::Cometd(QDeclarativeEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
{
}

QObject *Cometd::createInstance()
{
    QDeclarativeContext *rootContext = m_engine->rootContext();
    QDeclarativeContext *cometdContext = new QDeclarativeContext(rootContext);

    // Cometd-JavaScript depends on window.setTimeout and friends
    cometdContext->setContextProperty("timerWindow", new TimerWindow(this));

    QDeclarativeComponent component(m_engine, QUrl("qrc:/cometd.qml"));
    QObject *instance = component.create(cometdContext);
    cometdContext->setParent(instance);

    return instance;
}
