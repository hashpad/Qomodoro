#pragma once


#include <iostream>
using namespace std;

class Timer {
public:
    Timer(int length, int current);

    int getLength() const;
    void setLength(int newLength);
    int getCurrent() const;
    void setCurrent(int newCurrent);

    void increment();
    void reset();


    int getLeft() const;

    int getSecondsLeft() const;
    int getMinutesLeft() const;

    string getLeftString() const;
    string getLengthString() const;

    ~Timer();


private:
    int length;
    int current;
};
