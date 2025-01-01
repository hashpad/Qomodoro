#pragma once

#include "about.h"
#include "chart.h"
#include "database.h"
#include "pomodoro.h"
#include "preferences.h"
#include "stopwatch.h"
#include <QMainWindow>
#include <QTimer>

enum STATES { PREF = 1, ABOUT = 2, QUIT = 3 };
enum TIMER_TAB_PAGES { START = 0, POMODORO = 1 };

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_nextMonth_clicked();

  void on_prevMonth_clicked();

  void on_nextWeek_clicked();

  void on_prevWeek_clicked();

  void on_prevDay_clicked();
  void on_nextDay_clicked();

  void on_changePomodoroState_currentIndexChanged(int index);

  void on_toolsCombo_currentIndexChanged(int index);

  void on_startBtn_clicked();

  void on_togglePause_clicked();

  void on_skip_clicked();

  void reset();

  void update_cycles();
  void update_stopwatch();

private:
  QString get_cache_location();
  bool init_db();
  Ui::MainWindow *ui;
  Preferences *pref;
  About *about;
  Pomodoro *pm;
  Stopwatch *sw;
  Database *db;
  Chart *chart;
};
