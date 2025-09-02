#include "pomodoro.h"
#include <qlocale.h>
#include <qlogging.h>



Pomodoro::Pomodoro(QObject *parent, Stopwatch *sw, Database *db)
  : QObject{parent}, sw(sw), db(db), player(new QMediaPlayer(this)), audio_output(new QAudioOutput(this)) {
  update_ticking_preference();
}

void Pomodoro::update_ticking_preference() {
  if (sw && db) {
    sw->set_ticking_enabled(db->get_ticking_sound());
  }
}


void Pomodoro::set_state(PomodoroState ps, bool count_cycle) {
  state = ps;
  qInfo() << "current state is " << state;
  switch (ps) {
    case PomodoroState::PM:
      sw->set_goal(pm_duration);
      break;
    case PomodoroState::SB:
      sw->set_goal(break_duration);
      break;
    case PomodoroState::LB:
      sw->set_goal(long_break_duration);
      break;
  }
  sw->reset();
  if (!count_cycle)
    return;

  if (ps == PomodoroState::PM) {
    inc_cycles();
  } else if (ps == PomodoroState::LB) {
    current_cycle = 0;
  }
}


void Pomodoro::inc_cycles() {
  if (current_cycle == cycles)
    current_cycle = 0;
  else
    ++current_cycle;
  emit update_cycles();
}


PomodoroState Pomodoro::change_state() {
  // save to persist in db
  auto last_sw_value = sw->get_save();
  if (state == PomodoroState::PM) {
    db->insert_pm(last_sw_value, QDate::currentDate());

    player->setAudioOutput(audio_output);
    QString source(db->get_start_break_sound());
    qInfo() << "playing " << source;
    player->setSource(QUrl::fromLocalFile(source));
    player->play();
    qInfo() << "current cycles" << current_cycle;
    qInfo() << "target cycles" << cycles;
    if (current_cycle == cycles) {
      set_state(PomodoroState::LB, false);
      current_cycle = 0;
    } else {
      set_state(PomodoroState::SB, false);
      ++current_cycle;
    }
  } else {
    db->insert_break(last_sw_value, QDate::currentDate());
    set_state(PomodoroState::PM, false);
    player->setAudioOutput(audio_output);
    QString source(db->get_end_break_sound());
    qInfo() << "playing " << source;
    player->setSource(QUrl::fromLocalFile(source));
    player->play();
  }
  sw->reset();
  qInfo() << "state changed" << state;
  emit state_changed();
  return state;
}


bool Pomodoro::toggle_running() { return (running = !running); }
bool Pomodoro::is_running() const { return running; }

void Pomodoro::stop() {
  running = false;
  sw->set_goal(pm_duration);
  sw->reset();
}

int Pomodoro::get_pm_duration() const { return pm_duration; }
int Pomodoro::get_break_duration() const { return break_duration; }
int Pomodoro::get_long_break_duration() const { return long_break_duration; }
int Pomodoro::get_cycles() const { return cycles; }
int Pomodoro::get_cycles_left() const { return cycles - current_cycle; }
PomodoroState Pomodoro::get_state() const { return state; }

void Pomodoro::set_pm_duration(int value) {
  pm_duration = value;
  if (state == PomodoroState::PM)
    sw->set_goal(pm_duration);
}

void Pomodoro::set_break_duration(int value) {
  break_duration = value;
  if (state == PomodoroState::SB)
    sw->set_goal(break_duration);
}

void Pomodoro::set_long_break_duration(int value) {
  long_break_duration = value;
  if (state == PomodoroState::LB)
    sw->set_goal(long_break_duration);
}

void Pomodoro::set_cycles(int value) { cycles = value - 1; }

void Pomodoro::reset_sw() { sw->reset(); }

Pomodoro::~Pomodoro() = default;
