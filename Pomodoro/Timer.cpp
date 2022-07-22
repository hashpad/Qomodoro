#include "Timer.h"


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
    if(this->current < this->length)
        ++this->current;
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

    return to_string(this->getMinutesLeft()) + ":" + to_string(this->getSecondsLeft());
}

Timer::~Timer()
{
    delete qTimer;
}

Timer::Timer(int length, int current) : length(length),
    current(current)
{}
