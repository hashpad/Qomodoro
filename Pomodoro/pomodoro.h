#pragma once

#include <QTimer>
#include "pomodorostate.h"
class PomodoroState;
class FocusState;
class ShortBreakState;
class LongBreakState;

class LengthObserver;
class Object {
public:
    void subscribeObserverFocus(LengthObserver* focus);
    void unsubscribeObserverFocus();
    void notifyObserverFocus(int newLength);

    void subscribeObserverShortBreak(LengthObserver* shortBreak);
    void unsubscribeObserverShortBreak();
    void notifyObserverShortBreak(int newLength);

    void subscribeObserverLongBreak(LengthObserver* longBreak);
    void unsubscribeObserverLongBreak();
    void notifyObserverLongBreak(int newLength);
protected:
    LengthObserver* focus = nullptr;
    LengthObserver* shortBreak = nullptr;
    LengthObserver* longBreak = nullptr;
};

class Pomodoro : public QObject, public Object {
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

    int getShortBreakCount() const;
    int getMaxShortBreaks() const;

    void saveFocus(int length);
    void saveBreak(int length);

private:

    PomodoroState* activeState;

    QTimer* qTimer;

    bool isRunning;

    QObject* parent;

    int shortBreakCount = 0, maxShortBreaks;

    int pomodoroDuration, shortBreakDuration, longBreakDuration;


signals:
    emit void stateChange();
    emit void stateDone();

    emit void emitSaveBreak(QDate date, int length);
    emit void emitSaveFocus(QDate date, int length);
};
