#pragma once

#include "pomodoro.h"

#include "timer.h"

#include <iostream>
using namespace std;

class Pomodoro;
class LengthObserver {
public:
    virtual void updateLength(int newLength) = 0;
    virtual ~LengthObserver() {};
};

class PomodoroState : public QObject, public LengthObserver {
    Q_OBJECT;
public:
    PomodoroState() {};

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
    virtual void setTimer(Timer* newTimer) {
        timer = newTimer;
    };
    virtual void updateLength(int newLength) {
        if(timer)
            timer->setLength(newLength);
    }
    virtual void save() = 0;
protected:
    std::string name;
    Timer* timer;
    Pomodoro* pomodoroContext;
};
class FocusState : public PomodoroState {
    // PomodoroState interface
public:
    FocusState();
    void increment() override;
    string getName() const override;
    static string getStaticName();
    void setTimer(Timer* newTimer) override;
    void setPomodoroContext(Pomodoro* pomodoroContext) override;;
    void save() override;
};
class ShortBreakState : public PomodoroState {
    // PomodoroState interface
public:
    ShortBreakState();
    void increment() override;
    string getName() const override;
    static string getStaticName();
    void setTimer(Timer* newTimer) override;
    void setPomodoroContext(Pomodoro* pomodoroContext) override;;
    void save() override;
};
class LongBreakState : public PomodoroState {
    // PomodoroState interface
public:
    LongBreakState();
    void increment() override;
    string getName() const override;
    static string getStaticName();
    void setTimer(Timer* newTimer) override;
    void setPomodoroContext(Pomodoro* pomodoroContext) override;;
    void save() override;
};
