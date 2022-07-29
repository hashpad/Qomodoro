#include "pomodorostate.h"

#include <QDebug>

FocusState::FocusState(): PomodoroState(){
};

void FocusState::increment()
{
    if(!pomodoroContext) return;
    if(timer->getCurrent() < timer->getLength()) {
        timer->increment();
    }
    else if(!pomodoroContext->isLongBreak()) {
        qDebug() << "not a long break";
        pomodoroContext->incrementShortBreakCount();
        qDebug() << "number of short breaks is " << pomodoroContext->getShortBreakCount() << "/" << pomodoroContext->getMaxShortBreaks();
        pomodoroContext->setActiveState(new ShortBreakState());
    }else {
        pomodoroContext->resetShortBreakCount();
        qDebug() << "number of short breaks is " << pomodoroContext->getShortBreakCount() << "/" << pomodoroContext->getMaxShortBreaks();
        pomodoroContext->setActiveState(new LongBreakState());
    }
}
string FocusState::getName() const
{
    return FocusState::getStaticName();
}

string FocusState::getStaticName()
{
    return "Pomodoro";
}

void FocusState::setTimer(Timer *newTimer)
{
    timer = newTimer;
    if(pomodoroContext)
        timer->setLength(pomodoroContext->getPomodoroDuration());
}

void FocusState::setPomodoroContext(Pomodoro *pomodoroContext) {
    this->pomodoroContext = pomodoroContext;
    qDebug() << "there i state";
    pomodoroContext->subscribeObserverFocus(this);
}

ShortBreakState::ShortBreakState(): PomodoroState(){};

void ShortBreakState::increment()
{
    if(!pomodoroContext) return;
    if(timer->getCurrent() < timer->getLength()) {
        timer->increment();
    }
    else {
        pomodoroContext->setActiveState(new FocusState());
    }
}

string ShortBreakState::getName() const
{
    return ShortBreakState::getStaticName();
}

string ShortBreakState::getStaticName()
{
    return "Short break";
}
void ShortBreakState::setTimer(Timer *newTimer)
{
    timer = newTimer;
    if(pomodoroContext)
        timer->setLength(pomodoroContext->getShortBreakDuration());
}

void ShortBreakState::setPomodoroContext(Pomodoro *pomodoroContext) {
    this->pomodoroContext = pomodoroContext;
    pomodoroContext->subscribeObserverShortBreak(this);
}

LongBreakState::LongBreakState(): PomodoroState(){};

void LongBreakState::increment()
{
    if(!pomodoroContext) return;
    if(timer->getCurrent() < timer->getLength()) {
        timer->increment();
    }
    else {
        qDebug() << "back to focus";
        pomodoroContext->setActiveState(new FocusState());
    }
}


string LongBreakState::getName() const
{
    return LongBreakState::getStaticName();
}

string LongBreakState::getStaticName()
{
    return "Long break";
}

void LongBreakState::setTimer(Timer *newTimer)
{
    timer = newTimer;
    if(pomodoroContext)
        timer->setLength(pomodoroContext->getLongBreakDuration());
}

void LongBreakState::setPomodoroContext(Pomodoro *pomodoroContext) {
    this->pomodoroContext = pomodoroContext;
    pomodoroContext->subscribeObserverLongBreak(this);
}
