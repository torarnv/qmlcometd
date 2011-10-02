#ifndef BINDING_H
#define BINDING_H

#include <QObject>
#include <QScriptValue>

class Binding : public QObject
{
    Q_OBJECT
public:
    explicit Binding(QObject *parent = 0);

    Q_INVOKABLE void setForwardFunction(const QScriptValue &function);
    Q_INVOKABLE QScriptValue forward(const QScriptValue &name, const QScriptValue &arguments = QScriptValue());

private:
    QScriptValue m_forwardFunction;
};

#endif // BINDING_H
