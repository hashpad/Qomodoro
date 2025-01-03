#pragma once

#include <QObject>

class Stopwatch : public QObject {
  Q_OBJECT
public:
  explicit Stopwatch(QObject *parent = nullptr, const int value = 0);
  // decrement stopwatch until it reaches 0, then emit signal to change state
  void dec();
  // get stopwatch value in the form mm:ss
  QString as_string();
  // set stopwatch value, it also sets the "save" value
  void set_goal(const int value);
  // get current stopwatch value
  int get_value();
  // get starting stopwatch value
  int get_save();
  // reset to saved value
  void reset();

private:
  // stopwatch current value in seconds
  int value;
  // stopwatch starting value in seconds
  int save;

signals:
  // used to publish that the stopwatch has reached 0
  void change_state();
};
