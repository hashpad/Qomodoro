#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "preferences.h"

#include "Pomodoro/Pomodoro.h"
#include "Pomodoro/Timer.h"

Timer timer = Timer(3600, 0);
Pomodoro pomodoro = Pomodoro(timer, false);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QBarSet *set0 = new QBarSet("today");

    *set0 << 39 << 5;

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "Pomodoro" << "Break";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);

    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->leftTimeLbl->setText(QString::fromStdString(pomodoro.getTimer().getLeftString()));
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
        timer.getQTimer()->stop();
        delete timer.getQTimer();
    }
}

void MainWindow::increment_timer() {
    pomodoro.getTimer().increment();
    update_left_label();
}


void MainWindow::on_stopBtn_clicked()
{
    if(pomodoro.getIsRunning()) {
        on_runningBtn_clicked();
        pomodoro.getTimer().reset();
    }
    else {
        pomodoro.getTimer().reset();
    }
    update_left_label();
}


void MainWindow::update_left_label() {
    ui->leftTimeLbl->setText(QString::fromStdString(pomodoro.getTimer().getLeftString()));
}

void MainWindow::on_settingsBtn_clicked()
{
    Preferences* pref = new Preferences(this);
    pref->show();
}

