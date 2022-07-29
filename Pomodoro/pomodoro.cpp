#include "pomodoro.h"

#include <QMediaPlayer>
#include <QDebug>

using namespace std;


Pomodoro::Pomodoro(QObject* _parent):
    parent(_parent),
    isRunning(false)
{
    qDebug() << "created pomodoro";
}

bool Pomodoro::getIsRunning() const
{
    return isRunning;
}

void Pomodoro::setIsRunning(bool newIsRunning)
{
    isRunning = newIsRunning;
}

PomodoroState* Pomodoro::getActiveState() const {
    return activeState;
}
void Pomodoro::setActiveState(PomodoroState* const newState) {
    bool done = false;
    qDebug() << done;

    if(activeState) {
        qDebug() << "there is active state";
        done = activeState->getTimer()->getLeft() == 0;
        qDebug() << "done";
        delete activeState;
    }
    activeState = newState;
    activeState->setPomodoroContext(this);
    qDebug() << "set context succe";
    activeState->setTimer(new Timer());
    qDebug() << "set after timer succe";
    if(!done)
        emit stateChange();
    else
        emit stateDone();
}

Pomodoro::~Pomodoro() {
    delete activeState;
    delete qTimer;
}

int Pomodoro::getPomodoroDuration() const
{
    return pomodoroDuration;
}

void Pomodoro::setPomodoroDuration(int newPomodoroDuration)
{
    pomodoroDuration = newPomodoroDuration;
    if(focus) {
        notifyObserverFocus(newPomodoroDuration);
    }
}

int Pomodoro::getShortBreakDuration() const
{
    return shortBreakDuration;
}

void Pomodoro::setShortBreakDuration(int newShortBreakDuration)
{
    shortBreakDuration = newShortBreakDuration;
    if(shortBreak){
        notifyObserverShortBreak(newShortBreakDuration);
    }
}

int Pomodoro::getLongBreakDuration() const
{
    return longBreakDuration;
}

void Pomodoro::setLongBreakDuration(int newLongBreakDuration)
{
    longBreakDuration = newLongBreakDuration;
    if(longBreak) {
        notifyObserverLongBreak(newLongBreakDuration);
    }
}

QTimer * const Pomodoro::getQTimer() const
{
    return this->qTimer;
}

void Pomodoro::setQTimer(QTimer *newQTimer)
{

    this->qTimer = newQTimer;
}

void Pomodoro::incrementShortBreakCount()
{
    ++shortBreakCount;
}
void Pomodoro::resetShortBreakCount()
{
    shortBreakCount = 0;
}

bool Pomodoro::isLongBreak()
{
    return maxShortBreaks - shortBreakCount == 0;
}

void Pomodoro::setMaxShortBreaks(int newMaxShortBreaks) {
    maxShortBreaks = newMaxShortBreaks;
}

int Pomodoro::getShortBreakCount() const
{
    return shortBreakCount;
}

int Pomodoro::getMaxShortBreaks() const
{
    return maxShortBreaks;
}

void Object::subscribeObserverFocus(LengthObserver* focus)
{
    this->focus = focus;
    unsubscribeObserverShortBreak();
    unsubscribeObserverLongBreak();
}

void Object::unsubscribeObserverFocus()
{
    focus = nullptr;
}


void Object::subscribeObserverShortBreak(LengthObserver* shortBreak)
{
    unsubscribeObserverFocus();
    this->shortBreak = shortBreak;
    unsubscribeObserverLongBreak();
}

void Object::unsubscribeObserverShortBreak()
{
    shortBreak = nullptr;
}


void Object::subscribeObserverLongBreak(LengthObserver* longBreak)
{
    unsubscribeObserverFocus();
    unsubscribeObserverShortBreak();
    this->longBreak = longBreak;
}

void Object::unsubscribeObserverLongBreak()
{
    longBreak = nullptr;
}

void Object::notifyObserverFocus(int newLength)
{
    if(focus != nullptr)
        focus->updateLength(newLength);
}

void Object::notifyObserverShortBreak(int newLength)
{
    if(shortBreak != nullptr)
        shortBreak->updateLength(newLength);
}

void Object::notifyObserverLongBreak(int newLength)
{
    if(longBreak != nullptr)
        longBreak->updateLength(newLength);
}
