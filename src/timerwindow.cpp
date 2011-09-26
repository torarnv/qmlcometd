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
