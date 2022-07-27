#include "timer.h"


#include <iostream>

using namespace std;

int Timer::getLength() const
{
    return length;
}

void Timer::setLength(int newLength)
{
    length = newLength;
}

int Timer::getCurrent() const
{
    return current;
}

void Timer::setCurrent(int newCurrent)
{
    current = newCurrent;
}

void Timer::increment()
{
    ++this->current;
}

void Timer::reset()
{
    this->current = 0;
}


QTimer * const Timer::getQTimer() const
{
    return this->qTimer;
}

void Timer::setQTimer(QTimer *newQTimer)
{

    this->qTimer = newQTimer;
}

int Timer::getLeft() const
{
    return this->length - this->current;
}

int Timer::getSecondsLeft() const
{
    return this->getLeft() % 60;
}

int Timer::getMinutesLeft() const
{
    return this->getLeft() / 60;
}

string Timer::getLeftString() const
{
    string sec = to_string(this->getSecondsLeft());
    string min = to_string(this->getMinutesLeft());
    if(sec.length() == 1) sec = "0" + sec;
    return min + ":" + sec;
}

string Timer::getLengthString() const
{
    int min = length / 60;
    return to_string(min) + "min";
}

Timer::~Timer()
{
    delete qTimer;
}

Timer::Timer(int length, int current) : length(length),
    current(current)
{}
