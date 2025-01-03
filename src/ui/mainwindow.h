#pragma once

#include "about.h"
#include "core/chart.h"
#include "core/pomodoro.h"
#include "core/stopwatch.h"
#include "data/database.h"
#include "preferences.h"
#include <QMainWindow>
#include <QTimer>
#include <qvariant.h>

enum STATES { PREF = 1, ABOUT = 2, QUIT = 3 };
enum TIMER_TAB_PAGES { START = 0, POMODORO = 1 };
enum MAIN_TABS { TIMER = 0, STATS = 1 };

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  void ui_set_tab(unsigned char tab);
  void ui_set_page(unsigned char page);
  void ui_update_cycles_left();

  void ui_set_chart_view(QChartView *qchart_view, QChart *new_chart);

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
  void update_state();

private:
  void create_objects();
  void start_global_timer(unsigned int fire_each);
  void connect_signals();
  QString get_cache_location();

  Pomodoro *pm;
  Stopwatch *sw;
  Database *db;

  Chart *chart;
  Ui::MainWindow *ui;
  Preferences *pref;
  About *about;
};
