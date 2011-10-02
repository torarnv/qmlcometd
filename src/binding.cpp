#include "binding.h"

Binding::Binding(QObject *parent)
    : QObject(parent)
{
}

void Binding::setForwardFunction(const QScriptValue &function)
{
    Q_ASSERT(function.isFunction());
    m_forwardFunction = function;
}

QScriptValue Binding::forward(const QScriptValue &name, const QScriptValue &arguments)
{
    QScriptValueList args;
    args << name << arguments;

    return m_forwardFunction.call(QScriptValue(), args);
}
