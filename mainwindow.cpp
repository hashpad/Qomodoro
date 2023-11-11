#include <QTimer>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCharts>

enum Tools { PREF = 1, ABOUT = 2, QUIT = 3 };
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timerStacked->setCurrentIndex(0);
    db = new Database(this, "/home/" + QDir::home().dirName() + "/Qomodoro/pomodoro.db");

    sw = new Stopwatch(this);
    pm = new Pomodoro(this, sw);



    pref = new Preferences(this, pm);


    pm->set_pm_duration(pref->get_pm_duration());
    pm->set_break_duration(pref->get_break_duration());
    pm->set_long_break_duration(pref->get_long_break_duration());
    pm->set_cycles(pref->get_cycles());
    pm->set_db(db);
    ui->cyclesLeft->setText(QString::number(pm->get_cycles_left()));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_stopwatch);
    timer->start(100);

    connect(sw, &Stopwatch::change_state, pm, &Pomodoro::change_state);
    connect(pref, &Preferences::update_stopwatch, this, &MainWindow::update_stopwatch);
    connect(pref, &Preferences::update_cycles, this, &MainWindow::update_cycles);

    QBarSet *set0 = new QBarSet("Value");

    *set0 << 1 << 2;

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
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    ui->chartView->setChart(chart);
}


MainWindow::~MainWindow()
{
    delete pref;
    delete pm;
    delete sw;
    delete ui;
}


void MainWindow::update_stopwatch() {
    if(pm->is_running()){
        sw->dec();
        ui->stopwatch->setText(sw->as_string());
    }
}

void MainWindow::update_cycles() {
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
    this->update_stopwatch();
    ui->timerStacked->setCurrentIndex(1);
}


void MainWindow::on_togglePause_clicked()
{
    pm->set_running();
    ui->togglePause->setText(pm->is_running() ? "Pause" : "Start");
    ui->skip->setText(pm->is_running() ? "Skip" : "Stop");
}


void MainWindow::on_skip_clicked()
{
    if(ui->skip->text() == "Stop") this->reset();
    if(ui->skip->text() == "Skip") this->pm->change_state();
    this->update_stopwatch();
    this->update_cycles();
}


void MainWindow::reset() {
    ui->timerStacked->setCurrentIndex(0);
    ui->skip->setText("Skip");
    ui->togglePause->setText("Pause");
    ui->stopwatch->setText("--:--");
    pm->stop();
}



void MainWindow::on_changeState_currentIndexChanged(int index)
{
    this->pm->set_state((PomodoroState)index);
    this->update_stopwatch();
    this->update_cycles();
}

