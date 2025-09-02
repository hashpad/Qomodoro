  // Update ticking sound preference
  void update_ticking_preference();
#pragma once

#include <QAudioOutput>
#include <QDate>
#include <QDebug>
#include <QObject>
#include <QtMultimedia/QMediaPlayer>

#include "data/database.h"
#include "stopwatch.h"

enum PomodoroState {
  PM = 0,
  SB = 1,
  LB = 2,
};

class Pomodoro : public QObject {
  Q_OBJECT
public:
  explicit Pomodoro(QObject *parent = nullptr, Stopwatch *sw = nullptr, Database *db = nullptr);
  ~Pomodoro() override;

  bool is_running() const;
  // Returns current running state and then toggles it
  bool toggle_running();
  void stop();
  void update_ticking_preference();

  int get_pm_duration() const;
  int get_break_duration() const;
  int get_long_break_duration() const;
  int get_cycles() const;
  int get_cycles_left() const;
  PomodoroState get_state() const;

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

  int pm_duration = 0;
  int break_duration = 0;
  int long_break_duration = 0;
  int cycles = 0;
  int current_cycle = 0;
  bool running = false;
};
