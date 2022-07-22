#pragma once
#include "Timer.h"

class Pomodoro {
public:
    enum State {
        POMODORO,
        LONG_BREAK,
        SHORT_BREAK,
    };
    Pomodoro(Timer* timer, bool isRunning);

    Timer* getTimer() const;
    void setTimer(Timer *newTimer);

    bool getIsRunning() const;
    void setIsRunning(const bool newIsRunning);

    State getState() const;
    void setState(const State newState);

    string stateAsString(State state) const;


private:
    State state;
    Timer* timer;
    bool isRunning;

    map<State, string> mappedState = {{State::POMODORO, "pomodoro"},
                                      {State::SHORT_BREAK, "short break"},
                                      {State::LONG_BREAK, "long break"}};
};
