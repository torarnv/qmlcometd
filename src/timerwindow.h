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
