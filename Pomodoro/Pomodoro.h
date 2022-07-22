#pragma once
#include "Timer.h"
#include "../ui/mainwindow.h"

class Pomodoro {
public:
    Pomodoro(Timer &timer, bool isRunning);
    Timer &getTimer() const;
    void setTimer(const Timer &newTimer);
    bool getIsRunning() const;
    void setIsRunning(bool newIsRunning);

    Ui::MainWindow* const getUi() const;
    void setUi(Ui::MainWindow* ui);

    void run();

private:
    Timer& timer;
    bool isRunning;
    Ui::MainWindow* ui;
};
