#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "preferences.h"
#include "pomodoro.h"
#include "stopwatch.h"

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
    void on_changeState_currentIndexChanged(int index);

private slots:

    void on_toolsCombo_currentIndexChanged(int index);

    void on_startBtn_clicked();

    void on_togglePause_clicked();

    void on_skip_clicked();

    void reset();

    void update();

private:
    Ui::MainWindow *ui;
    Preferences* pref;
    Pomodoro* pm;
    Stopwatch* sw;
};
#endif // MAINWINDOW_H
