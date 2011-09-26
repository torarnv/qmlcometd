#ifndef COMETD_H
#define COMETD_H

#include <QObject>

class QDeclarativeEngine;

class Cometd : public QObject
{
    Q_OBJECT
public:
    explicit Cometd(QDeclarativeEngine *engine, QObject *parent = 0);

    // TODO: Add public API for creating new instances
    QObject *createInstance();

private:
    QDeclarativeEngine *m_engine;
};

#endif // COMETD_H
