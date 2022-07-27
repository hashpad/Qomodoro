#pragma once
#include "Pomodoro/pomodoro.h"

#include <QMainWindow>

#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>


#include "preferences.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_leftLabel();
    void on_startPauseBtnClicked();
    void on_stopBtnClicked();
    void on_settingsBtnClicked();


    void on_leftValueUpdate();

    void incrementTimer();


private:
    Pomodoro* pomodoroModel;

    Ui::MainWindow *ui;
    Preferences *pref;

    QStringListModel* modeComboModel;



    QStringListModel* createModeComboModel();
};
