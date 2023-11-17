#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent, Pomodoro* pm, Database* db)
    : QDialog(parent)
    , ui(new Ui::Preferences)
    , pm(pm)
    , db(db)
{
    ui->setupUi(this);
    int pm_duration = db->get_pm_duration() / 60;
    ui->pmDurationLabel->setText(this->format_minutes(pm_duration));
    ui->pmDurationSlider->setSliderPosition(pm_duration);

    int break_duration = db->get_break_duration() / 60;
    ui->breakDurationLabel->setText(this->format_minutes(break_duration));
    ui->breakDurationSlider->setSliderPosition(break_duration);

    int long_break_duration = db->get_long_break_duration() / 60;
    ui->longBreakDurationLabel->setText(this->format_minutes(long_break_duration));
    ui->longBreakDurationSlider->setSliderPosition(long_break_duration);

    int ticking_sound = db->get_ticking_sound();

    ui->tickingSound->setCheckState((Qt::CheckState)ticking_sound);
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
    db->set_pm_duration(value*60);
    emit update();
}


void Preferences::on_breakDurationSlider_valueChanged(int value)
{
    ui->breakDurationLabel->setText(this->format_minutes(value));
    pm->set_break_duration(value*60);
    db->set_break_duration(value*60);
    emit update();
}


void Preferences::on_longBreakDurationSlider_valueChanged(int value)
{
    ui->longBreakDurationLabel->setText(this->format_minutes(value));
    pm->set_long_break_duration(value*60);
    db->set_long_break_duration(value*60);
    emit update();
}


void Preferences::on_pmCycles_valueChanged(int value)
{
    pm->set_cycles(value);
    db->set_cycles(value);
    emit update_cycles();
}




void Preferences::on_tickingSound_stateChanged(int arg1)
{
    db->set_ticking_sound(arg1);
}

