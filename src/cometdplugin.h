#ifndef COMETDPLUGIN_H
#define COMETDPLUGIN_H

#include <QDeclarativeExtensionPlugin>

class CometdPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void initializeEngine(QDeclarativeEngine *engine, const char *uri);
    void registerTypes(const char *uri);
};

#endif // COMETDPLUGIN_H
