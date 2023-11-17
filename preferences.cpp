#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent, Pomodoro* pm, Database* db)
    : QDialog(parent)
    , ui(new Ui::Preferences)
    , pm(pm)
    , db(db)
{
    ui->setupUi(this);
}

int Preferences::get_pm_duration() {
    return ui->pmDurationSlider->value()*60;
}
int Preferences::get_break_duration() {
    return ui->breakDurationSlider->value()*60;
}
int Preferences::get_long_break_duration() {
    return ui->longBreakDurationSlider->value()*60;
}
int Preferences::get_cycles() {
    return ui->pmCycles->value();
}

Preferences::~Preferences()
{
    delete ui;
}

QString Preferences::format_minutes(int value) {
    return QString::number(value).append(" minutes");
}
void Preferences::on_pmDurationSlider_valueChanged(int value)
{
    ui->pmDurationLabel->setText(this->format_minutes(value));
    pm->set_pm_duration(value*60);
    db->set_pm_duration(value);
    emit update();
}


void Preferences::on_breakDurationSlider_valueChanged(int value)
{
    ui->breakDurationLabel->setText(this->format_minutes(value));
    pm->set_break_duration(value*60);
    emit update();
}


void Preferences::on_longBreakDurationSlider_valueChanged(int value)
{
    ui->longBreakDurationLabel->setText(this->format_minutes(value));
    pm->set_long_break_duration(value*60);
    emit update();
}


void Preferences::on_pmCycles_valueChanged(int value)
{
    pm->set_cycles(value);
    emit update_cycles();
}



