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

#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <QList>
#include <QObject>
#include <QScriptValue>
#include <QTimer>

class Timer : public QTimer
{
    Q_OBJECT
public:
    Timer(QObject *parent, const QScriptValue &handler);
    void remove();

private Q_SLOTS:
    void handleTimeout();

private:
    QScriptValue m_handler;
};

class TimerWindow : public QObject
{
    Q_OBJECT
public:
    explicit TimerWindow(QObject *parent = 0);

    // FIXME: Handle extra handler arguments
    Q_INVOKABLE int setInterval(const QScriptValue &handler, long timeout);
    Q_INVOKABLE int setTimeout(const QScriptValue &handler, long timeout);
    Q_INVOKABLE void clearInterval(int timerId);
    Q_INVOKABLE void clearTimeout(int timerId);

private:
    int createTimer(const QScriptValue &handler, long timeout, bool singleshot);
    void removeTimer(int timerId);
};

#endif // TIMERWINDOW_H
