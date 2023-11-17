#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "preferences.h"
#include "pomodoro.h"
#include "stopwatch.h"
#include "database.h"
#include "chart.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_nextMonth_clicked();

private slots:
    void on_prevMonth_clicked();

private slots:
    void on_nextWeek_clicked();

private slots:
    void on_prevWeek_clicked();


private slots:
    void on_prevDay_clicked();
    void on_nextDay_clicked();


private slots:
    void on_changeState_currentIndexChanged(int index);

private slots:

    void on_toolsCombo_currentIndexChanged(int index);

    void on_startBtn_clicked();

    void on_togglePause_clicked();

    void on_skip_clicked();

    void reset();

    void update_cycles();
    void update_stopwatch();

private:
    Ui::MainWindow *ui;
    Preferences* pref;
    Pomodoro* pm;
    Stopwatch* sw;
    Database* db;
    Chart* chart;
};
#endif // MAINWINDOW_H
