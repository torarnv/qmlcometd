#include "cometdplugin.h"

#include "cometd.h"

#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>

void CometdPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri);

    Cometd *cometd = new Cometd(engine, this);
    engine->rootContext()->setContextProperty("Cometd", cometd);

    // Add a default instance
    engine->rootContext()->setContextProperty("cometd", cometd->createInstance());
}

void CometdPlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<Cometd>(uri, 1, 0, "Cometd", QString());
}

Q_EXPORT_PLUGIN2(cometdplugin, CometdPlugin);
