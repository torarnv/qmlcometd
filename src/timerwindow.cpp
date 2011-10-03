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

#include "timerwindow.h"

#include <QtGlobal>

Q_GLOBAL_STATIC(QList<Timer*> , activeTimers)

Timer::Timer(QObject *parent, const QScriptValue &handler)
    : QTimer(parent), m_handler(handler)
{
    connect(this, SIGNAL(timeout()), SLOT(handleTimeout()));
}

void Timer::handleTimeout()
{
    Q_ASSERT(m_handler.isFunction());

    m_handler.call();
    if (isSingleShot())
        remove();
}

void Timer::remove() {
    activeTimers()->removeAll(this);
    deleteLater();
}

namespace {
    // Per HTML5, section 7.3
    long s_minimumTimeout = 4;
}

TimerWindow::TimerWindow(QObject *parent) :
    QObject(parent)
{
}

int TimerWindow::setTimeout(const QScriptValue &handler, long timeout)
{
    return createTimer(handler, timeout, true);
}

int TimerWindow::setInterval(const QScriptValue &handler, long interval)
{
    return createTimer(handler, interval, false);
}

void TimerWindow::clearTimeout(int timerId)
{
    removeTimer(timerId);
}

void TimerWindow::clearInterval(int timerId)
{
    removeTimer(timerId);
}

int TimerWindow::createTimer(const QScriptValue &handler, long timeout, bool singleshot)
{
    if (!handler.isFunction())
        return -1;

    Timer *timer = new Timer(this, handler);
    timer->setInterval(qMax(timeout, long(s_minimumTimeout)));
    timer->setSingleShot(singleshot);
    activeTimers()->append(timer);
    timer->start();

    return timer->timerId();
}

void TimerWindow::removeTimer(int timerId)
{
    for (int i = 0; i < activeTimers()->count(); ++i) {
        Timer *timer = activeTimers()->at(i);
        if (timer->timerId() == timerId) {
            timer->remove();
            return;
        }
    }
}
