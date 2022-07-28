#pragma once

#include <QTimer>
#include "pomodorostate.h"
class PomodoroState;
class FocusState;
class ShortBreakState;
class LongBreakState;

class Pomodoro : public QObject {
Q_OBJECT
public:
    Pomodoro(QObject* _parent, bool isRunning, PomodoroState* activeState);

    bool getIsRunning() const;
    void setIsRunning(const bool newIsRunning);

    PomodoroState* getActiveState() const;
    void setActiveState(PomodoroState* const newState);

    QTimer* const getQTimer() const;
    void setQTimer(QTimer* newQTimer);

    ~Pomodoro();
private:

    PomodoroState* activeState;

    QTimer* qTimer;

    bool isRunning;

    QObject* parent;

signals:
    emit void stateChange();
    emit void stateDone();
};
