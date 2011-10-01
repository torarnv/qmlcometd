#ifndef COMETDPLUGIN_H
#define COMETDPLUGIN_H

#include <QDeclarativeExtensionPlugin>

class QDeclarativeEngine;

class CometdPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void initializeEngine(QDeclarativeEngine *engine, const char *uri);
    void registerTypes(const char *uri);

    static QDeclarativeEngine *engine() { return s_engine; }

private:
    static QDeclarativeEngine *s_engine;
};

#endif // COMETDPLUGIN_H
