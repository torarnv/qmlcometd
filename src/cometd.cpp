#include "cometd.h"
#include "cometdplugin.h"
#include "timerwindow.h"

#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>

Cometd::Cometd(QObject *parent)
    : QObject(parent)
{
    QDeclarativeEngine *engine = CometdPlugin::engine();
    QDeclarativeContext *rootContext = engine->rootContext();
    QDeclarativeContext *cometdContext = new QDeclarativeContext(rootContext);

    // Cometd-JavaScript depends on window.setTimeout and friends
    cometdContext->setContextProperty("timerWindow", new TimerWindow(this));

    // Allow the implementation to pass back the forward-function
    cometdContext->setContextProperty("wrapper", this);

    QDeclarativeComponent component(engine, QUrl("qrc:/cometd.qml"));
    QObject *implementation = component.create(cometdContext);
    cometdContext->setParent(implementation);
    implementation->setParent(this);

    QMetaObject::invokeMethod(implementation, "initialize");
}

void Cometd::setForwardFunction(const QScriptValue &function)
{
    Q_ASSERT(function.isFunction());
    m_forwardFunction = function;
}

QScriptValue Cometd::forward(const QScriptValue &name, const QScriptValue &arguments)
{
    QScriptValueList args;
    args << name << arguments;

    return m_forwardFunction.call(QScriptValue(), args);
}
