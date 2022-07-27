#include "Pomodoro.h"

#include <chrono>
#include <thread>


using namespace std;


Pomodoro::Pomodoro(bool isRunning, int pomodoro, int shortBreak, int longBreak) :
    pomodoro(pomodoro),
    shortBreak(shortBreak),
    longBreak(longBreak),
    timer(new Timer(pomodoro, 0)),
    isRunning(isRunning)
{
}


Timer *Pomodoro::getTimer() const
{
    return timer;
}

void Pomodoro::setTimer(Timer* newTimer)
{
    timer = newTimer;
}

bool Pomodoro::getIsRunning() const
{
    return isRunning;
}

void Pomodoro::setIsRunning(bool newIsRunning)
{
    isRunning = newIsRunning;
}

Pomodoro::State Pomodoro::getState() const {
    return state;
}
void Pomodoro::setState(const Pomodoro::State newState) {
    state = newState;
    switch(newState) {
        case(Pomodoro::State::POMODORO):
            timer->setLength(getPomodoro());
        break;
        case(Pomodoro::State::SHORT_BREAK):
            timer->setLength(getShortBreak());
        break;
        case(Pomodoro::State::LONG_BREAK):
            timer->setLength(getLongBreak());
        break;
    }
    timer->reset();
}

string Pomodoro::stateAsString(Pomodoro::State state) const {
    auto findIt = mappedState.find(state);
    return findIt->second;
}

void Pomodoro::setPomodoro(int newPomodoro)
{
    pomodoro = newPomodoro;
}

void Pomodoro::setShortBreak(int newShortBreak)
{
    shortBreak = newShortBreak;
}

void Pomodoro::setLongBreak(int newLongBreak)
{
    longBreak = newLongBreak;
}

int Pomodoro::getPomodoro() const {
    return pomodoro;
}
int Pomodoro::getShortBreak() const {
    return shortBreak;
}
int Pomodoro::getLongBreak() const {
    return longBreak;
}
