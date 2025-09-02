#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pomodoro.h"
#include <qlogging.h>
#include <qobject.h>

#define TIMER_SPEED 1000
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // setup needed objects (new)
  this->create_objects();

  this->ui_set_tab(MAIN_TABS::TIMER);
  // Start the timer tab at the start page
  // Start at the timer tab
  this->ui_set_page(TIMER_TAB_PAGES::START);

  // set the cycles left in the ui
  this->ui_update_cycles_left();

  // create a global timer, and make it fire each TIMER_SPEED
  this->start_global_timer(TIMER_SPEED);

  // connect different signals
  this->connect_signals();
}

void MainWindow::create_objects() {
  // create and init db
  QString cacheLocation = this->get_cache_location();
  db = new Database(this, cacheLocation + "/pomodoro.db");
  if (!db->init()) {
    qInfo() << "Error: connection to db failed";
    QApplication::quit();
  }
  // create a stopwatch
  sw = new Stopwatch(this);
  // create a pomodoro
  pm = new Pomodoro(this, sw, db);
  // create the preference ui
  pref = new Preferences(this, pm, db);
  // create the about ui
  about = new About(this);
  // setup pomodoro
  pm->set_pm_duration(pref->get_pm_duration());
  pm->set_break_duration(pref->get_break_duration());
  pm->set_long_break_duration(pref->get_long_break_duration());
  pm->set_cycles(pref->get_cycles());
  pm->set_state(PomodoroState::PM, false);
  qInfo() << "Pomodoro duration is set to " << pm->get_pm_duration();
  qInfo() << "Pomodoro short break is set to " << pm->get_break_duration();
  qInfo() << "Pomodoro long break is set to " << pm->get_long_break_duration();
  qInfo() << "Pomodoro state is set to " << pm->get_state();

  // setup the charts
  chart = new Chart(this, db);
  this->ui_set_chart_view(ui->dayChartView, chart->get_day_view_chart());
  this->ui_set_chart_view(ui->weekChartView, chart->get_week_view_chart());
  this->ui_set_chart_view(ui->monthChartView, chart->get_month_view_chart());
}
void MainWindow::ui_set_tab(unsigned char tab) {
  ui->mainTabs->setCurrentIndex(tab);
}
void MainWindow::ui_set_page(unsigned char page) {
  ui->timerTabPages->setCurrentIndex(page);
}
void MainWindow::ui_update_cycles_left() {
  ui->cyclesLeft->setText(QString::number(pm->get_cycles_left()));
}
void MainWindow::start_global_timer(unsigned int fire_each) {
  QTimer *timer = new QTimer(this);
  /* connect the timer
   after the amount defined by fire_each the timeout will fire */
  connect(timer, &QTimer::timeout, this, &MainWindow::update_stopwatch);
  timer->start(fire_each);
}

void MainWindow::connect_signals() {
  connect(sw, &Stopwatch::change_state, pm, &Pomodoro::change_state);

  connect(pm, &Pomodoro::update_cycles, this, &MainWindow::update_cycles);
  connect(pm, &Pomodoro::state_changed, this, &MainWindow::update_state);

  connect(pref, &Preferences::update, this, &MainWindow::update_stopwatch);
  connect(pref, &Preferences::update_cycles, this, &MainWindow::update_cycles);
  connect(pref, &Preferences::ticking_sound, this, &MainWindow::update_ticking_sound);
}

void MainWindow::update_ticking_sound() {
  sw->set_ticking_enabled(pref->get_ticking_sound());
}

void MainWindow::update_state() {
  ui->changePomodoroState->setCurrentIndex(pm->get_state());
}

void MainWindow::ui_set_chart_view(QChartView *qchart_view, QChart *new_chart) {
  auto *old_chart = qchart_view->chart();
  qchart_view->setChart(new_chart);
  delete old_chart;
}
QString MainWindow::get_cache_location() {
  QString cacheLocation =
      QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
  if (!QDir(cacheLocation).exists())
    QDir().mkdir(cacheLocation);
  return cacheLocation;
}

void MainWindow::update_stopwatch() {
  ui->stopwatch->setText(sw->as_string());
  if (pm->is_running())
    sw->dec();
}

void MainWindow::update_cycles() {
  ui->cyclesLeft->setText(QString::number(pm->get_cycles_left()));
}

// ------------ EVENT HANDLING -----------------------------------------
void MainWindow::on_toolsCombo_currentIndexChanged(int index) {
  if (index == PREF) {
    this->pref->show();
  }
  if (index == ABOUT) {
    this->about->show();
  }
  if (index == QUIT) {
    QApplication::quit();
  }
  ui->toolsCombo->setCurrentIndex(0);
}

void MainWindow::on_startBtn_clicked() {
  ui->timerTabPages->setCurrentIndex(TIMER_TAB_PAGES::POMODORO);
  pm->toggle_running();
  this->pm->set_state(PomodoroState::PM, false);
  this->update_state();
  this->update_stopwatch();
  this->update_cycles();
}

void MainWindow::on_togglePause_clicked() {
  pm->toggle_running();
  ui->togglePause->setText(pm->is_running() ? "Pause" : "Start");
  ui->skip->setText(pm->is_running() ? "Skip" : "Stop");
}

void MainWindow::on_skip_clicked() {
  if (ui->skip->text() == "Stop") {
    this->reset();
  } else if (ui->skip->text() == "Skip") {
    this->pm->change_state();
  }
  this->update_stopwatch();
  this->update_cycles();
}

void MainWindow::reset() {
  ui->timerTabPages->setCurrentIndex(TIMER_TAB_PAGES::START);
  ui->skip->setText("Skip");
  ui->togglePause->setText("Pause");
  ui->stopwatch->setText("--:--");
  pm->stop();
}

void MainWindow::on_changePomodoroState_currentIndexChanged(int index) {
  this->pm->set_state((PomodoroState)index, false);
  this->update_stopwatch();
  this->update_cycles();
}

void MainWindow::on_prevDay_clicked() {
  this->chart->set_day_offset(this->chart->get_day_offset() - 1);
  this->ui_set_chart_view(ui->dayChartView, chart->get_day_view_chart());
  ui->dayNameLabel->setText(this->chart->get_day_name());
  ui->nextDay->setEnabled(this->chart->get_day_offset());
}
void MainWindow::on_nextDay_clicked() {
  this->chart->set_day_offset(this->chart->get_day_offset() + 1);
  this->ui_set_chart_view(ui->dayChartView, chart->get_day_view_chart());
  ui->dayNameLabel->setText(this->chart->get_day_name());
  ui->nextDay->setEnabled(this->chart->get_day_offset());
}

void MainWindow::on_prevWeek_clicked() {
  this->chart->set_week_offset(this->chart->get_week_offset() - 1);
  this->ui_set_chart_view(ui->weekChartView, chart->get_week_view_chart());
  ui->weekNameLabel->setText(this->chart->get_week_name());
  ui->nextWeek->setEnabled(this->chart->get_week_offset());
}

void MainWindow::on_nextWeek_clicked() {
  this->chart->set_week_offset(this->chart->get_week_offset() + 1);
  this->ui_set_chart_view(ui->weekChartView, chart->get_week_view_chart());
  ui->weekNameLabel->setText(this->chart->get_week_name());
  ui->nextWeek->setEnabled(this->chart->get_week_offset());
}

void MainWindow::on_prevMonth_clicked() {
  this->chart->set_month_offset(this->chart->get_month_offset() - 1);
  this->ui_set_chart_view(ui->monthChartView, chart->get_month_view_chart());
  ui->monthNameLabel->setText(this->chart->get_month_name());
  ui->nextMonth->setEnabled(this->chart->get_month_offset());
}

void MainWindow::on_nextMonth_clicked() {
  this->chart->set_month_offset(this->chart->get_month_offset() + 1);
  this->ui_set_chart_view(ui->monthChartView, chart->get_month_view_chart());
  ui->monthNameLabel->setText(this->chart->get_month_name());
  ui->nextMonth->setEnabled(this->chart->get_month_offset());
}
MainWindow::~MainWindow() {}
