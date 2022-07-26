#pragma once
#include "Pomodoro/pomodoro.h"
#include "Pomodoro/database.h"

#include <QMainWindow>

#include <QMediaPlayer>

#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

#include <QSettings>


#include "preferences.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void exit();
    ~MainWindow();

private slots:
    void update_leftLabel();
    void update_modeCombo();
    void on_startPauseBtnClicked();
    void on_stopBtnClicked();
    void on_settingsBtnClicked();

    void triggerNotification();
    void modeChange();
    void modeDone();
    void startPomodoro();
    void pausePomodoro();
    void stopPomodoro();

    void startMedia(int playFor);
    void stopMedia();

    void on_leftValueUpdate();

    void incrementTimer();


    void on_modeComboCurrentTextChanged(const QString &arg1);

private:
    Pomodoro* pomodoroModel;

    Ui::MainWindow *ui;
    Preferences *pref;

    QStringListModel* modeComboModel;

    QMediaPlayer* mediaPlayer;
    QTimer* mediaQtimer;

    QSettings settings = QSettings("Qomodoro", "Qomodoro");
    Database db;


    int pomodoroDuration, shortBreakDuration, longBreakDuration;

    QStringListModel* createModeComboModel();
    // replace with from to
    QChart* createCharts(QDate date);



};
