/**************************************************************************
**
**  Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
**  All rights reserved.
**
**  Contact: Nokia Corporation (qt-info@nokia.com)
**
**  You may use this file under the terms of the BSD license as follows:
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are
**  met:
**
**    * Redistributions of source code must retain the above copyright
**      notice, this list of conditions and the following disclaimer.
**
**    * Redistributions in binary form must reproduce the above copyright
**      notice, this list of conditions and the following disclaimer in
**      the documentation and/or other materials provided with the
**      distribution.
**
**    * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**      the names of its contributors may be used to endorse or promote
**      products derived from this software without specific prior written
**      permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
**  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
**  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
**  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
**  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
**  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
**  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
**  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
**  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "cometd.h"

#include "binding.h"
#include "cometdplugin.h"
#include "timerwindow.h"

#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>

Cometd::Cometd(QObject *parent)
    : QObject(parent)
    , m_binding(new Binding(this))
{
    QDeclarativeEngine *engine = CometdPlugin::engine();
    QDeclarativeContext *rootContext = engine->rootContext();
    QDeclarativeContext *cometdContext = new QDeclarativeContext(rootContext);

    // Cometd-JavaScript depends on window.setTimeout and friends
    cometdContext->setContextProperty("timerWindow", new TimerWindow(this));

    // Allow the implementation to pass back the forward-function
    cometdContext->setContextProperty("binding", m_binding);

    cometdContext->setContextProperty("application", qApp);

    QDeclarativeComponent component(engine, QUrl("qrc:/cometd.qml"));
    QObject *implementation = component.create(cometdContext);
    cometdContext->setParent(implementation);
    implementation->setParent(this);

    QMetaObject::invokeMethod(implementation, "initialize");
}

QScriptValue Cometd::forward(const QScriptValue &name, const QScriptValue &arguments)
{
    return m_binding->forward(name, arguments);
}
