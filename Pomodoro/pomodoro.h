#pragma once

#include "pomodorostate.h"

class Pomodoro {
public:
    Pomodoro(bool isRunning, PomodoroState* initialState);

    bool getIsRunning() const;
    void setIsRunning(const bool newIsRunning);

    PomodoroState* getState() const;
    void setState(PomodoroState* newState);

    ~Pomodoro();
private:
    PomodoroState* state;
    bool isRunning;
};
