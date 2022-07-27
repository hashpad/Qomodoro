#include "pomodorostate.h"



FocusState::FocusState(Timer* timer): PomodoroState(timer){};

void FocusState::increment()
{
    if(timer->getCurrent() < timer->getLength())
        timer->increment();
}
string FocusState::getName() const
{
    return FocusState::getStaticName();
}

string FocusState::getStaticName()
{
    return "Pomodoro";
}
ShortBreakState::ShortBreakState(Timer* timer): PomodoroState(timer){};

void ShortBreakState::increment()
{
    if(timer->getCurrent() < timer->getLength())
        timer->increment();
}

string ShortBreakState::getName() const
{
    return ShortBreakState::getStaticName();
}

string ShortBreakState::getStaticName()
{
    return "Short break";
}
LongBreakState::LongBreakState(Timer* timer): PomodoroState(timer){};

void LongBreakState::increment()
{
    if(timer->getCurrent() < timer->getLength())
        timer->increment();
}


string LongBreakState::getName() const
{
    return LongBreakState::getStaticName();
}

string LongBreakState::getStaticName()
{
    return "Long break";
}
