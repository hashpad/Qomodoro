#pragma once

#include <QAudioOutput>
#include <QDate>
#include <QDebug>
#include <QObject>
#include <QtMultimedia/QMediaPlayer>

#include "database.h"
#include "stopwatch.h"

enum PomodoroState {
  PM = 0,
  SB = 1,
  LB = 2,
};

class Pomodoro : public QObject {
  Q_OBJECT
public:
  explicit Pomodoro(QObject *parent = nullptr, Stopwatch *sw = nullptr,
                    Database *db = nullptr);
  ~Pomodoro();
  bool is_running();
  // returns current running states and then toggles it
  bool toggle_running();
  void stop();

  int get_pm_duration();
  int get_break_duration();
  int get_long_break_duration();
  int get_cycles();
  int get_cycles_left();
  PomodoroState get_state();

  void set_pm_duration(int value);
  void set_break_duration(int value);
  void set_long_break_duration(int value);
  void set_cycles(int value);
  void set_state(PomodoroState ps, bool count_cycle);

  void reset_sw();

  void inc_cycles();
public slots:
  PomodoroState change_state();

signals:
  void update_cycles();
  void state_changed();

private:
  PomodoroState state;
  Stopwatch *sw;
  Database *db;
  QMediaPlayer *player;
  QAudioOutput *audio_output;

  int pm_duration;
  int break_duration;
  int long_break_duration;
  int cycles;
  int current_cycle = 0;
  bool running = false;
};
