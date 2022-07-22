#pragma once
#include <iostream>

#include <QTimer>
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

    QTimer* const getQTimer() const;
    void setQTimer(QTimer* newQTimer);

    int getLeft() const;

    int getSecondsLeft() const;
    int getMinutesLeft() const;

    string getLeftString() const;
    string getLengthString() const;

    ~Timer();


private:
    int length;
    int current;
    QTimer* qTimer;
};
