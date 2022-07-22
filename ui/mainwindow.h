#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

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
    void increment_timer();
    void update_left_label();
    void on_runningBtn_clicked();
    void on_stopBtn_clicked();

    void on_settingsBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
