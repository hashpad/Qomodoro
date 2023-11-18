#include "pomodoro.h"


Pomodoro::Pomodoro(QObject *parent, Stopwatch* sw, int pm_duration, int break_duration, int long_break_duration, int cycles, Database* db)
    : QObject{parent}, sw(sw), pm_duration(pm_duration), break_duration(break_duration), long_break_duration(long_break_duration), cycles(cycles), db(db)
{
    this->state = PomodoroState::PM;
    this->sw->set_value(pm_duration);
    this->player = new QMediaPlayer;
    this->audio_output = new QAudioOutput;
}

bool Pomodoro::is_running() {return this->running;}
bool Pomodoro::set_running() {
    return (this->running=!this->running);
}
void Pomodoro::stop() {
    this->running = false;
    this->sw->set_value(this->pm_duration);
}

int Pomodoro::get_pm_duration() { return this->pm_duration; }
int Pomodoro::get_break_duration() { return this->break_duration; }
int Pomodoro::get_long_break_duration() { return this->long_break_duration; }
int Pomodoro::get_cycles() { return this->cycles; }

void Pomodoro::set_pm_duration(int value) { this->pm_duration = value;  reset_stopwatch(); }
void Pomodoro::set_break_duration(int value) { this->break_duration = value; reset_stopwatch(); }
void Pomodoro::set_long_break_duration(int value) { this->long_break_duration = value; reset_stopwatch(); }
void Pomodoro::set_cycles(int value) { this->cycles = value; }
void Pomodoro::set_db(Database* db) { this->db = db; }

PomodoroState Pomodoro::change_state() {
    auto last_sw_value = this->sw->get_save();
    if(this->state == PM) {
        this->db->add_pomodoro(last_sw_value, QDate::currentDate());

        player->setAudioOutput(audio_output);
        QString source(db->get_start_break_sound());
        qInfo() << "playing " << source;
        player->setSource(QUrl::fromLocalFile(source));
        player->play();
        if(current_cycle == cycles) {
            this->state = LB;
            this->current_cycle = 0;
        }
        else {
            this->state = SB;
            ++this->current_cycle;
        }
    } else {
        this->db->add_break(last_sw_value, QDate::currentDate());
        this->state = PM;
        player->setAudioOutput(audio_output);
        QString source(db->get_end_break_sound());
        qInfo() << "playing " << source;
        player->setSource(QUrl::fromLocalFile(source));
        player->play();
    }
    this->reset_stopwatch();
    qInfo() << "state changed" << this->state;
    return this->state;
}
void Pomodoro::inc_cycles() {
    if (this->current_cycle == this->cycles)
        this->current_cycle = 0;
    else ++this->current_cycle;
}

void Pomodoro::set_state(PomodoroState ps) {
    this->state = ps;
    if(ps == PM) {
        this->inc_cycles();
    }else if(ps == LB) {
        this->current_cycle = 0;
    }
    this->reset_stopwatch();
}
PomodoroState Pomodoro::get_state() {
    return this->state;
}

void Pomodoro::reset_stopwatch() {
    if(this->state == PM) this->sw->set_value(this->pm_duration);
    if(this->state == SB) this->sw->set_value(this->break_duration);
    if(this->state == LB) this->sw->set_value(this->long_break_duration);
}

int Pomodoro::get_cycles_left() {
    return this->cycles - this->current_cycle;
}

Pomodoro::~Pomodoro() {
    delete player;
    delete audio_output;
}
