#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>

#include "pomodoro.h"

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = nullptr, Pomodoro* pm = nullptr, Database* db = nullptr);
    int get_pm_duration();
    int get_break_duration();
    int get_long_break_duration();
    int get_cycles();

    ~Preferences();


private slots:
    void on_tickingSound_stateChanged(int arg1);

private slots:
    void on_pmCycles_valueChanged(int arg1);

private slots:
    void on_pmDurationSlider_valueChanged(int value);

    void on_breakDurationSlider_valueChanged(int value);

    void on_longBreakDurationSlider_valueChanged(int value);

signals:
    void update_stopwatch();
    void update_cycles();
private:
    Ui::Preferences *ui;
    Pomodoro *pm;
    Database *db;

    QString format_minutes(int value);
};

#endif // PREFERENCES_H
