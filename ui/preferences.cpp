#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent, Pomodoro* pomodoroModel) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    this->pomodoroModel = pomodoroModel;


    updatePomodoroDurationLbl();

    connect(ui->pomodoroDurationSlider, &QSlider::sliderMoved, this, &Preferences::on_horizontalSliderValueChanged);
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

void Preferences::on_horizontalSliderValueChanged(int value)
{
    pomodoroModel->getActiveState()->getTimer()->setLength(value*60);
    updatePomodoroDurationLbl();
    emit leftValueUpdate();
}


void Preferences::updatePomodoroDurationLbl() {
    ui->pomodoroDurationLbl->setText(QString::fromStdString(pomodoroModel->getActiveState()->getTimer()->getLengthString()));
    ui->pomodoroDurationSlider->setValue(pomodoroModel->getActiveState()->getTimer()->getLength() / 60);
}
