#ifndef POMODORO_H
#define POMODORO_H

#include <QObject>

#include "stopwatch.h"
#include "database.h"

enum PomodoroState {
    PM,
    SB,
    LB,
};

class Pomodoro : public QObject
{
    Q_OBJECT
public:
    explicit Pomodoro(QObject *parent = nullptr, Stopwatch *sw = nullptr, int pomodoro_duration = 0, int break_duration = 0, int long_break_duration = 0, int cycles = 0, Database* db = nullptr);
    bool is_running();
    bool set_running();
    void stop();
    void reset_stopwatch();
    void set_state(PomodoroState ps);
    PomodoroState get_state();
    void inc_cycles();

    int get_pm_duration();
    int get_break_duration();
    int get_long_break_duration();
    int get_cycles();
    int get_cycles_left();

    void set_pm_duration(int value);
    void set_break_duration(int value);
    void set_long_break_duration(int value);
    void set_cycles(int value);
    void set_db(Database* db);



public slots:
    PomodoroState change_state();


signals:



private:
    PomodoroState state;
    Stopwatch* sw;
    Database* db;
    int pm_duration;
    int break_duration;
    int long_break_duration;
    int cycles;
    int current_cycle = 0;
    bool running = false;
};

#endif // POMODORO_H
