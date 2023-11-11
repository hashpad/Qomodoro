#include <QTimer>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

enum Tools { PREF = 1, ABOUT = 2, QUIT = 3 };
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timerStacked->setCurrentIndex(0);
    sw = new Stopwatch(this);
    pm = new Pomodoro(this, sw);



    pref = new Preferences(this, pm);


    pm->set_pm_duration(pref->get_pm_duration());
    pm->set_break_duration(pref->get_break_duration());
    pm->set_long_break_duration(pref->get_long_break_duration());
    pm->set_cycles(pref->get_cycles());
    ui->cyclesLeft->setText(QString::number(pm->get_cycles_left()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    connect(sw, &Stopwatch::change_state, pm, &Pomodoro::change_state);
    connect(pref, &Preferences::update, this, &MainWindow::update);

}


MainWindow::~MainWindow()
{
    delete pref;
    delete pm;
    delete sw;
    delete ui;
}


void MainWindow::update() {
    if(pm->is_running()){
        sw->dec();
        ui->stopwatch->setText(sw->as_string());
    }
    ui->cyclesLeft->setText(QString::number(pm->get_cycles_left()));
}


void MainWindow::on_toolsCombo_currentIndexChanged(int index)
{
    if(index == PREF) {
        this->pref->show();
    }
    ui->toolsCombo->setCurrentIndex(0);
}


void MainWindow::on_startBtn_clicked()
{
    pm->set_running();
    this->update();
    ui->timerStacked->setCurrentIndex(1);
}


void MainWindow::on_togglePause_clicked()
{
    pm->set_running();
    ui->togglePause->setText(pm->is_running() ? "Pause" : "Start");
    ui->skip->setText(pm->is_running() ? "Skip" : "Stop");
    this->update();
}


void MainWindow::on_skip_clicked()
{
    if(ui->skip->text() == "Stop") this->reset();
    this->update();
}


void MainWindow::reset() {
    ui->timerStacked->setCurrentIndex(0);
    ui->stopwatch->setText("--:--");
    pm->stop();
}



void MainWindow::on_changeState_currentIndexChanged(int index)
{
    this->pm->set_state((PomodoroState)index);
    this->update();
}

