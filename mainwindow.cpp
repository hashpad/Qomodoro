#include "mainwindow.h"
#include "./ui_mainwindow.h"

enum Tools { PREF = 1, ABOUT = 2, QUIT = 3 };
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timerStacked->setCurrentIndex(0);

    QString cacheLocation = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    if(!QDir(cacheLocation).exists()) QDir().mkdir(cacheLocation);

    db = new Database(this, cacheLocation + "/pomodoro.db");


    sw = new Stopwatch(this);
    pm = new Pomodoro(this, sw);



    pref = new Preferences(this, pm, db);
    about = new About(this);


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

    chart = new Chart(this, db);

    ui->dayChartView->setChart(chart->get_day_view_chart());
    ui->weekChartView->setChart(chart->get_week_view_chart());
    ui->monthChartView->setChart(chart->get_month_view_chart());
}


MainWindow::~MainWindow()
{
    delete pref;
    delete about;
    delete pm;
    delete sw;
    delete db;
    delete ui;
    delete chart;
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
    if(index == ABOUT) {
        this->about->show();
    }
    if(index == QUIT) {
        QApplication::quit();
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




void MainWindow::on_prevDay_clicked()
{
    this->chart->set_day_offset(this->chart->get_day_offset() - 1);
    ui->dayChartView->setChart(chart->get_day_view_chart());
    ui->dayNameLabel->setText(this->chart->get_day_name());
    ui->nextDay->setEnabled(this->chart->get_day_offset());
}
void MainWindow::on_nextDay_clicked()
{
    this->chart->set_day_offset(this->chart->get_day_offset() + 1);
    ui->dayChartView->setChart(chart->get_day_view_chart());
    ui->dayNameLabel->setText(this->chart->get_day_name());
    ui->nextDay->setEnabled(this->chart->get_day_offset());
}



void MainWindow::on_prevWeek_clicked()
{
    this->chart->set_week_offset(this->chart->get_week_offset() - 1);
    ui->weekChartView->setChart(chart->get_week_view_chart());
    ui->weekNameLabel->setText(this->chart->get_week_name());
    ui->nextWeek->setEnabled(this->chart->get_week_offset());
}


void MainWindow::on_nextWeek_clicked()
{
    this->chart->set_week_offset(this->chart->get_week_offset() + 1);
    ui->weekChartView->setChart(chart->get_week_view_chart());
    ui->weekNameLabel->setText(this->chart->get_week_name());
    ui->nextWeek->setEnabled(this->chart->get_week_offset());
}


void MainWindow::on_prevMonth_clicked()
{
    this->chart->set_month_offset(this->chart->get_month_offset() - 1);
    ui->monthChartView->setChart(chart->get_month_view_chart());
    ui->monthNameLabel->setText(this->chart->get_month_name());
    ui->nextMonth->setEnabled(this->chart->get_month_offset());
}


void MainWindow::on_nextMonth_clicked()
{
    this->chart->set_month_offset(this->chart->get_month_offset() + 1);
    ui->monthChartView->setChart(chart->get_month_view_chart());
    ui->monthNameLabel->setText(this->chart->get_month_name());
    ui->nextMonth->setEnabled(this->chart->get_month_offset());
}

