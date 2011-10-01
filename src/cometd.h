#ifndef COMETD_H
#define COMETD_H

#include <QObject>
#include <QScriptValue>

class QDeclarativeEngine;

class Cometd : public QObject
{
    Q_OBJECT
public:
    explicit Cometd(QObject *parent = 0);

    Q_INVOKABLE void setForwardFunction(const QScriptValue &function);
    Q_INVOKABLE QScriptValue forward(const QScriptValue &name, const QScriptValue &arguments);

private:
    QScriptValue m_forwardFunction;
};

#endif // COMETD_H
