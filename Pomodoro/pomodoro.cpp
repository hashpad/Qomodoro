#include "pomodoro.h"


#include <QDebug>

using namespace std;


Pomodoro::Pomodoro(bool isRunning, PomodoroState* activeState):
    isRunning(isRunning),
    activeState(activeState)
{
    this->activeState->setPomodoroContext(this);
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
    if(activeState)
        delete activeState;
    activeState = newState;
    activeState->setPomodoroContext(this);
}

Pomodoro::~Pomodoro() {
    delete activeState;
    delete qTimer;
}

QTimer * const Pomodoro::getQTimer() const
{
    return this->qTimer;
}

void Pomodoro::setQTimer(QTimer *newQTimer)
{

    this->qTimer = newQTimer;
}
