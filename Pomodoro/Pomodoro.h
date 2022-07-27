#pragma once
#include "Timer.h"

class Pomodoro {
public:
    enum State {
        POMODORO,
        LONG_BREAK,
        SHORT_BREAK,
    };
    Pomodoro(bool isRunning, int pomodoro, int shortBreak, int longBreak);

    Timer* getTimer() const;
    void setTimer(Timer *newTimer);

    bool getIsRunning() const;
    void setIsRunning(const bool newIsRunning);

    State getState() const;
    void setState(const State newState);

    string stateAsString(State state) const;

    int getPomodoro() const;
    int getShortBreak() const;
    int getLongBreak() const;


    void setPomodoro(int newPomodoro);
    void setShortBreak(int newShortBreak);
    void setLongBreak(int newLongBreak);

private:
    State state;
    Timer* timer;
    bool isRunning;

    int pomodoro, shortBreak, longBreak;

    map<State, string> mappedState = {{State::POMODORO, "pomodoro"},
                                      {State::SHORT_BREAK, "short break"},
                                      {State::LONG_BREAK, "long break"}};
};
