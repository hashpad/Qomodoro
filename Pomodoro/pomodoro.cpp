#include "pomodoro.h"



using namespace std;


Pomodoro::Pomodoro(bool isRunning, PomodoroState* initialState):
    state(initialState),
    isRunning(isRunning)
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

PomodoroState* Pomodoro::getState() const {
    return state;
}
void Pomodoro::setState(PomodoroState* newState) {
    state = newState;
}

Pomodoro::~Pomodoro() {
    delete state;
}
