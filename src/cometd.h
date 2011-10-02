#ifndef COMETD_H
#define COMETD_H

#include <QObject>
#include <QScriptValue>

class Binding;

class QDeclarativeEngine;

class Cometd : public QObject
{
    Q_OBJECT
public:
    explicit Cometd(QObject *parent = 0);

    Q_INVOKABLE QScriptValue forward(const QScriptValue &name, const QScriptValue &arguments = QScriptValue());

private:
    Binding *m_binding;
};

#endif // COMETD_H
