#pragma once

#include "Pomodoro/Timer.h"
#include "Pomodoro/Pomodoro.h"

Timer timer = Timer(3600, 0);
Pomodoro pomodoro = Pomodoro(timer, false);
