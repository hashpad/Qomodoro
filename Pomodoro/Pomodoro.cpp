#include "Pomodoro.h"

#include <chrono>
#include <thread>


using namespace std;


Pomodoro::Pomodoro(Timer &timer, bool isRunning) : timer(timer),
    isRunning(isRunning)
{
}

void Pomodoro::run() {
    while(isRunning) {
        this->timer.setCurrent(this->timer.getCurrent()+1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

Timer &Pomodoro::getTimer() const
{
    return timer;
}

void Pomodoro::setTimer(const Timer &newTimer)
{
    timer = newTimer;
}

bool Pomodoro::getIsRunning() const
{
    return isRunning;
}

void Pomodoro::setIsRunning(bool newIsRunning)
{
    isRunning = newIsRunning;
}

void Pomodoro::setUi(Ui::MainWindow* ui) {
    this->ui = ui;
}
Ui::MainWindow* const Pomodoro::getUi() const {
    return this->ui;
}
