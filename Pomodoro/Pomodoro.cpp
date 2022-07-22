#include "Pomodoro.h"

#include <chrono>
#include <thread>


using namespace std;


Pomodoro::Pomodoro(Timer* timer, bool isRunning) :
    timer(timer),
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
}

string Pomodoro::stateAsString(Pomodoro::State state) const {
    auto findIt = mappedState.find(state);
    return findIt->second;
}
