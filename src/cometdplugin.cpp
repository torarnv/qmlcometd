#include "cometdplugin.h"
#include "cometd.h"

#include <QDeclarativeComponent>

QDeclarativeEngine *CometdPlugin::s_engine = 0;

void CometdPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri);

    // FIXME: Can we detect if client code includes us based on the uri?

    s_engine = engine;
}

void CometdPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Cometd>(uri, 1, 0, "Cometd");
}

Q_EXPORT_PLUGIN2(cometdplugin, CometdPlugin);
