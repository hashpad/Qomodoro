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
    explicit Preferences(QWidget *parent = nullptr, Pomodoro* pm = nullptr);
    int get_pm_duration();
    int get_break_duration();
    int get_long_break_duration();
    int get_cycles();

    ~Preferences();

private slots:
    void on_pmDurationSlider_valueChanged(int value);

    void on_breakDurationSlider_valueChanged(int value);

    void on_longBreakDurationSlider_valueChanged(int value);

signals:
    void update();
private:
    Ui::Preferences *ui;
    Pomodoro *pm;

    QString format_minutes(int value);
};

#endif // PREFERENCES_H
