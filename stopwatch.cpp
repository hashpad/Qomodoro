#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent, int value)
    : QObject{parent}, value(value)
{
}

void Stopwatch::dec() {
    if (this->value > 0)
      this->value--;
    else
        emit change_state();
}

QString Stopwatch::as_string() {
    QString str;
    auto minutes = QString::number(this->value/60);
    if(minutes.length() == 1) minutes.prepend('0');
    auto seconds = QString::number(this->value%60);
    if(seconds.length() == 1) seconds.prepend('0');

    str.append(minutes);
    str.append(":");
    str.append(seconds);
    return str;
}

void Stopwatch::set_value(const int value) {this->value = value; this->save = value; }
int Stopwatch::get_value() {return this->value;}
int Stopwatch::get_save() {return this->save;}
