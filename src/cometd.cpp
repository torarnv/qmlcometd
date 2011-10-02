#include "cometd.h"

#include "binding.h"
#include "cometdplugin.h"
#include "timerwindow.h"

#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>

Cometd::Cometd(QObject *parent)
    : QObject(parent)
    , m_binding(new Binding(this))
{
    QDeclarativeEngine *engine = CometdPlugin::engine();
    QDeclarativeContext *rootContext = engine->rootContext();
    QDeclarativeContext *cometdContext = new QDeclarativeContext(rootContext);

    // Cometd-JavaScript depends on window.setTimeout and friends
    cometdContext->setContextProperty("timerWindow", new TimerWindow(this));

    // Allow the implementation to pass back the forward-function
    cometdContext->setContextProperty("binding", m_binding);

    QDeclarativeComponent component(engine, QUrl("qrc:/cometd.qml"));
    QObject *implementation = component.create(cometdContext);
    cometdContext->setParent(implementation);
    implementation->setParent(this);

    QMetaObject::invokeMethod(implementation, "initialize");
}

QScriptValue Cometd::forward(const QScriptValue &name, const QScriptValue &arguments)
{
    return m_binding->forward(name, arguments);
}
