#pragma once

#include "pomodoro.h"

#include "timer.h"

#include <iostream>
using namespace std;

class Pomodoro;
class PomodoroState {
public:
    PomodoroState(Timer* timer) : timer(timer) {};

    Timer* getTimer() const {
        return timer;
    }
    virtual void increment() = 0;
    virtual void setPomodoroContext(Pomodoro* pomodoroContext) {
       this->pomodoroContext = pomodoroContext;
    };
    virtual std::string getName() const = 0;
    virtual ~PomodoroState() {
        delete timer;
    };
protected:
    std::string name;
    Timer* timer;
    Pomodoro* pomodoroContext;
};
class FocusState : public PomodoroState {
    // PomodoroState interface
public:
    FocusState(Timer* timer);
    void increment() override;
    string getName() const override;
    static string getStaticName();
};
class ShortBreakState : public PomodoroState {
    // PomodoroState interface
public:
    ShortBreakState(Timer* timer);
    void increment() override;
    string getName() const override;
    static string getStaticName();
};
class LongBreakState : public PomodoroState {
    // PomodoroState interface
public:
    LongBreakState(Timer* timer);
    void increment() override;
    string getName() const override;
    static string getStaticName();
};
