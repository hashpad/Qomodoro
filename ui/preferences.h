#pragma once

#include "Pomodoro/pomodoro.h"

#include <QDialog>

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

signals:
    emit void leftValueUpdate();

private slots:
    void on_horizontalSliderValueChanged(int value);


private:
    Ui::Preferences *ui;

    Pomodoro* pomodoroModel;

    void updatePomodoroDurationLbl();
};
