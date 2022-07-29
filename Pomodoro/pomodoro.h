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
    Pomodoro(QObject* _parent);

    bool getIsRunning() const;
    void setIsRunning(const bool newIsRunning);

    PomodoroState* getActiveState() const;
    void setActiveState(PomodoroState* const newState);

    QTimer* const getQTimer() const;
    void setQTimer(QTimer* newQTimer);

    void incrementShortBreakCount();
    void resetShortBreakCount();
    bool isLongBreak();

    ~Pomodoro();
    int getPomodoroDuration() const;
    void setPomodoroDuration(int newPomodoroDuration);
    int getShortBreakDuration() const;
    void setShortBreakDuration(int newShortBreakDuration);
    int getLongBreakDuration() const;
    void setLongBreakDuration(int newLongBreakDuration);

    void setMaxShortBreaks(int newMaxShortBreaks);

private:

    PomodoroState* activeState;

    QTimer* qTimer;

    bool isRunning;

    QObject* parent;

    int shortBreakCount = 0, maxShortBreaks = 4;

    int pomodoroDuration, shortBreakDuration, longBreakDuration;


signals:
    emit void stateChange();
    emit void stateDone();
};
