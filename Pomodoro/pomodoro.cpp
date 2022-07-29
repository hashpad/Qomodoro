#include "pomodoro.h"

#include <QMediaPlayer>
#include <QDebug>

using namespace std;


Pomodoro::Pomodoro(QObject* _parent):
    parent(_parent),
    isRunning(false)
{
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

    if(activeState)
        done = activeState->getTimer()->getLeft() == 0;
        delete activeState;
    activeState = newState;
    activeState->setPomodoroContext(this);
    activeState->setTimer(new Timer());
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
    if(activeState)
        activeState->getTimer()->setLength(newPomodoroDuration);
}

int Pomodoro::getShortBreakDuration() const
{
    return shortBreakDuration;
}

void Pomodoro::setShortBreakDuration(int newShortBreakDuration)
{
    shortBreakDuration = newShortBreakDuration;
    if(activeState)
        activeState->getTimer()->setLength(newShortBreakDuration);
}

int Pomodoro::getLongBreakDuration() const
{
    return longBreakDuration;
}

void Pomodoro::setLongBreakDuration(int newLongBreakDuration)
{
    longBreakDuration = newLongBreakDuration;
    if(activeState)
        activeState->getTimer()->setLength(newLongBreakDuration);
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
    return shortBreakCount == maxShortBreaks;
}

void Pomodoro::setMaxShortBreaks(int newMaxShortBreaks) {
    newMaxShortBreaks = newMaxShortBreaks;
}
