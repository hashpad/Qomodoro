#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent, Pomodoro* pomodoroModel) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    setWindowTitle("Preferences");

    this->pomodoroModel = pomodoroModel;

    loadSettings();

    connect(ui->pomodoroDurationSlider, &QSlider::sliderMoved, this, &Preferences::on_pomodoroDurationSliderMoved);
    connect(ui->pomodoroDurationSlider, &QSlider::sliderReleased, this, &Preferences::on_pomodoroDurationSliderReleased);

    connect(ui->shortBreakDurationSlider, &QSlider::sliderMoved, this, &Preferences::on_shortBreakDurationSliderMoved);
    connect(ui->shortBreakDurationSlider, &QSlider::sliderReleased, this, &Preferences::on_shortBreakDurationSliderReleased);

    connect(ui->longBreakDurationSlider, &QSlider::sliderMoved, this, &Preferences::on_longBreakDurationSliderMoved);
    connect(ui->longBreakDurationSlider, &QSlider::sliderReleased, this, &Preferences::on_longBreakDurationSliderReleased);
}

Preferences::~Preferences()
{
    delete ui;
}

Ui::Preferences *Preferences::getUi() const
{
    return ui;
}

Pomodoro *Preferences::getPomodoroModel() const
{
    return pomodoroModel;
}


void Preferences::setUi(Ui::Preferences *newUi)
{
    ui = newUi;
}

void Preferences::setPomodoroModel(Pomodoro *newPomodoroModel)
{
    pomodoroModel = newPomodoroModel;
}

void Preferences::updatePomodoroDuration(int value) {
    pomodoroModel->setPomodoroDuration(value*60);
    updatePomodoroDurationLbl(value);
}
void Preferences::on_pomodoroDurationSliderReleased()
{
    int value = ui->pomodoroDurationSlider->value();
    updatePomodoroDuration(value);
    saveSettings();
}

void Preferences::on_pomodoroDurationSliderMoved(int value)
{
    updatePomodoroDuration(value);
}

void Preferences::updateShortBreakDuration(int value) {
    pomodoroModel->setShortBreakDuration(value*60);
    updateShortBreakDurationLbl(value);
}
void Preferences::on_shortBreakDurationSliderReleased()
{
    int value = ui->shortBreakDurationSlider->value();
    updateShortBreakDuration(value);
    saveSettings();
}

void Preferences::on_shortBreakDurationSliderMoved(int value)
{
    updateShortBreakDuration(value);
}
void Preferences::updateLongBreakDuration(int value) {
    pomodoroModel->setLongBreakDuration(value*60);
    updateLongBreakDurationLbl(value);
}
void Preferences::on_longBreakDurationSliderReleased()
{
    int value = ui->longBreakDurationSlider->value();
    updateLongBreakDuration(value);
    saveSettings();
}

void Preferences::on_longBreakDurationSliderMoved(int value)
{
    updateLongBreakDuration(value);
}

void Preferences::updatePomodoroDurationLbl(int value) {
    ui->pomodoroDurationLbl->setText(QString::number(value) + " min");
}
void Preferences::updateShortBreakDurationLbl(int value) {
    ui->shortBreakDurationLbl->setText(QString::number(value) + " min");
}
void Preferences::updateLongBreakDurationLbl(int value) {
    ui->longBreakDurationLbl->setText(QString::number(value) + " min");
}

void Preferences::saveSettings() {
    QSettings setting("Qomodoro", "Qomodoro");
    setting.beginGroup("MainWindow");
    setting.setValue("pomodoro_duration", this->ui->pomodoroDurationSlider->value());
    setting.setValue("short_break_duration", this->ui->shortBreakDurationSlider->value());
    setting.setValue("max_short_breaks", this->ui->pomodorosB4LongBreak->value());
    setting.endGroup();
}

void Preferences::loadSettings() {
    QSettings setting("Qomodoro", "Qomodoro");
    setting.beginGroup("MainWindow");
    ui->pomodoroDurationSlider->setValue(setting.value("pomodoro_duration").toInt());
    ui->pomodoroDurationLbl->setText(setting.value("pomodoro_duration").toString() + " min");

    ui->shortBreakDurationSlider->setValue(setting.value("short_break_duration", 5).toInt());
    ui->shortBreakDurationLbl->setText(setting.value("short_break_duration", 5).toString() + " min");

    ui->longBreakDurationSlider->setValue(setting.value("long_break_duration", 30).toInt());
    ui->longBreakDurationLbl->setText(setting.value("long_break_duration", 30).toString() + " min");

    ui->pomodorosB4LongBreak->setValue(setting.value("max_short_breaks", 4).toInt());
    setting.endGroup();
}

void Preferences::on_pomodorosB4LongBreakValueChanged(int value)
{
    updatePomodorosB4LongBreak(value);
    saveSettings();
}

void Preferences::updatePomodorosB4LongBreak(int value) {
    pomodoroModel->setMaxShortBreaks(value);
}
