#pragma once

#include "Pomodoro/pomodoro.h"

#include <QDialog>
#include <QSettings>

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = nullptr, Pomodoro* pomodoroModel = nullptr);
    ~Preferences();

    Ui::Preferences *getUi() const;
    Pomodoro *getPomodoroModel() const;

    void setUi(Ui::Preferences *newUi);
    void setPomodoroModel(Pomodoro *newPomodoroModel);

    void saveSettings();
    void loadSettings();

signals:
    emit void pomodoroDurationUpdate();

private slots:


    void on_pomodoroDurationSliderMoved(int value);
    void on_pomodoroDurationSliderReleased();


    void on_shortBreakDurationSliderMoved(int value);
    void on_shortBreakDurationSliderReleased();

    void on_longBreakDurationSliderMoved(int value);
    void on_longBreakDurationSliderReleased();

    void on_pomodorosB4LongBreakValueChanged(int value);

private:
    Ui::Preferences *ui;

    Pomodoro* pomodoroModel;

    QSettings settings;

    void updatePomodoroDurationLbl(int value);
    void updatePomodoroDuration(int value);

    void updateShortBreakDurationLbl(int value);
    void updateShortBreakDuration(int value);

    void updateLongBreakDurationLbl(int value);
    void updateLongBreakDuration(int value);

    void updatePomodorosB4LongBreak(int value);
};
