#include "pomodoro.h"
#include <qlocale.h>
#include <qlogging.h>

Pomodoro::Pomodoro(QObject *parent, Stopwatch *sw, Database *db)
    : QObject{parent}, sw(sw), db(db) {
  this->player = new QMediaPlayer(this);
  this->audio_output = new QAudioOutput(this);
}

void Pomodoro::set_state(PomodoroState ps, bool count_cycle) {
  this->state = ps;
  qInfo() << "current state is " << this->state;
  switch (ps) {
  case PomodoroState::PM:
    this->sw->set_goal(this->pm_duration);
    break;
  case PomodoroState::SB:
    this->sw->set_goal(this->break_duration);
    break;
  case PomodoroState::LB:
    this->sw->set_goal(this->long_break_duration);
    break;
  }
  this->sw->reset();
  if (!count_cycle)
    return;

  if (ps == PomodoroState::PM) {
    this->inc_cycles();
  } else if (ps == PomodoroState::LB) {
    this->current_cycle = 0;
  }
}

void Pomodoro::inc_cycles() {
  if (this->current_cycle == this->cycles)
    this->current_cycle = 0;
  else
    this->current_cycle++;
  emit update_cycles();
}

PomodoroState Pomodoro::change_state() {
  // save to persist in db
  auto last_sw_value = this->sw->get_save();
  if (this->state == PomodoroState::PM) {
    this->db->insert_pm(last_sw_value, QDate::currentDate());

    player->setAudioOutput(audio_output);
    QString source(db->get_start_break_sound());
    qInfo() << "playing " << source;
    player->setSource(QUrl::fromLocalFile(source));
    player->play();
    qInfo() << "current cycles" << current_cycle;
    qInfo() << "target cycles" << cycles;
    if (current_cycle == cycles) {
      this->set_state(PomodoroState::LB, false);
      this->current_cycle = 0;
    } else {
      this->set_state(PomodoroState::SB, false);
      this->current_cycle++;
    }
  } else {
    this->db->insert_break(last_sw_value, QDate::currentDate());
    this->set_state(PomodoroState::PM, false);
    player->setAudioOutput(audio_output);
    QString source(db->get_end_break_sound());
    qInfo() << "playing " << source;
    player->setSource(QUrl::fromLocalFile(source));
    player->play();
  }
  this->sw->reset();
  qInfo() << "state changed" << this->state;
  emit state_changed();
  return this->state;
}

bool Pomodoro::toggle_running() { return (this->running = !this->running); }
bool Pomodoro::is_running() { return this->running; }
void Pomodoro::stop() {
  this->running = false;
  this->sw->set_goal(this->pm_duration);
  this->sw->reset();
}
int Pomodoro::get_pm_duration() { return this->pm_duration; }
int Pomodoro::get_break_duration() { return this->break_duration; }
int Pomodoro::get_long_break_duration() { return this->long_break_duration; }
int Pomodoro::get_cycles() { return this->cycles; }
int Pomodoro::get_cycles_left() { return this->cycles - this->current_cycle; }
PomodoroState Pomodoro::get_state() { return this->state; }

void Pomodoro::set_pm_duration(int value) {
  this->pm_duration = value;
  if (this->state == PomodoroState::PM)
    this->sw->set_goal(this->pm_duration);
}
void Pomodoro::set_break_duration(int value) {
  this->break_duration = value;
  if (this->state == PomodoroState::SB)
    this->sw->set_goal(this->break_duration);
}
void Pomodoro::set_long_break_duration(int value) {
  this->long_break_duration = value;
  if (this->state == PomodoroState::LB)
    this->sw->set_goal(this->long_break_duration);
}
void Pomodoro::set_cycles(int value) { this->cycles = value - 1; }
void Pomodoro::reset_sw() { this->sw->reset(); }
Pomodoro::~Pomodoro() {}
