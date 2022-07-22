#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Pomodoro/Pomodoro.h"
#include "Pomodoro/Timer.h"

#include <QTimer>
#include <QDebug>


Timer timer = Timer(3599, 0);
Pomodoro pomodoro = Pomodoro(timer, false);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runningBtn_clicked()
{
    if(!pomodoro.getIsRunning()) {
        ui->runningBtn->setIcon(QIcon::fromTheme("media-playback-pause"));
        pomodoro.setIsRunning(true);
        timer.setQTimer(new QTimer(this));
        connect(timer.getQTimer(), SIGNAL(timeout()), this, SLOT(increment_timer()));
        timer.getQTimer()->start(1000);
    }else {
        ui->runningBtn->setIcon(QIcon::fromTheme("media-playback-start"));
        pomodoro.setIsRunning(false);
        delete timer.getQTimer();
    }
}

void MainWindow::increment_timer() {
    pomodoro.getTimer().increment();
    ui->leftTimeLbl->setText(QString::fromStdString(pomodoro.getTimer().getLeftString()));
    qDebug() << (QString::fromStdString(pomodoro.getTimer().getLeftString()));
}

