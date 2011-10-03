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
