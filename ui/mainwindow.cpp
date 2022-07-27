#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "preferences.h"
#include "preferences.h"

#include "Pomodoro/Pomodoro.h"
#include "Pomodoro/Timer.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , pomodoroModel(new Pomodoro(false, 5, 300 /* 5min */ , 600 /* 10 min */))

    , ui(new Ui::MainWindow)
    , pref(new Preferences(this, pomodoroModel))

    , modeComboModel(createModeComboModel())
{

    ui->setupUi(this);


    QBarSet *set0 = new QBarSet("today");

    *set0 << 39 << 5;

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
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);

    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    ui->modeCombo->setModel(modeComboModel);
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getTimer()->getLeftString()));




    connect(pref, &Preferences::leftValueUpdate, this, &MainWindow::on_leftValueUpdate);


    connect(this->ui->startPauseBtn, &QPushButton::clicked, this, &MainWindow::on_startPauseBtnClicked);
    connect(this->ui->stopBtn, &QPushButton::clicked, this, &MainWindow::on_stopBtnClicked);
    connect(this->ui->settingsBtn, &QPushButton::clicked, this, &MainWindow::on_settingsBtnClicked);
}

MainWindow::~MainWindow()
{
    delete pref;
    delete pomodoroModel;
    delete ui;
}

void MainWindow::on_startPauseBtnClicked()
{
    if(!this->pomodoroModel->getIsRunning()) {
        ui->startPauseBtn->setIcon(QIcon::fromTheme("media-playback-pause"));
        this->pomodoroModel->setIsRunning(true);
        this->pomodoroModel->getTimer()->setQTimer(new QTimer(this));
        connect(this->pomodoroModel->getTimer()->getQTimer(), &QTimer::timeout, this, &MainWindow::incrementTimer);
        this->pomodoroModel->getTimer()->getQTimer()->start(1000);
    }else {
        ui->startPauseBtn->setIcon(QIcon::fromTheme("media-playback-start"));
        this->pomodoroModel->setIsRunning(false);
        this->pomodoroModel->getTimer()->getQTimer()->stop();
        delete this->pomodoroModel->getTimer()->getQTimer();
    }
}

void MainWindow::incrementTimer() {
    auto* timer = this->pomodoroModel->getTimer();
    auto* pomodoro = this->pomodoroModel;
    if(timer->increment()){
        update_leftLabel();
    }
    else {
        pomodoro->setState(Pomodoro::State::SHORT_BREAK);
        incrementTimer();
    }

}


void MainWindow::on_stopBtnClicked()
{
    if(this->pomodoroModel->getIsRunning()) {
        on_startPauseBtnClicked();
        this->pomodoroModel->getTimer()->reset();
    }
    else {
        this->pomodoroModel->getTimer()->reset();
    }
    update_leftLabel();
}


void MainWindow::update_leftLabel() {
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getTimer()->getLeftString()));
}
void MainWindow::on_leftValueUpdate() {
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getTimer()->getLeftString()));
}

void MainWindow::on_settingsBtnClicked()
{
    pref->show();
}


QStringListModel* MainWindow::createModeComboModel() {
    QStringList* modeComboModel = new QStringList();
    *modeComboModel << QString::fromStdString(pomodoroModel->stateAsString(Pomodoro::State::POMODORO));
    *modeComboModel << QString::fromStdString(pomodoroModel->stateAsString(Pomodoro::State::SHORT_BREAK));
    *modeComboModel << QString::fromStdString(pomodoroModel->stateAsString(Pomodoro::State::LONG_BREAK));

    QStringListModel* modeModel = new QStringListModel(this);
    modeModel->setStringList(*modeComboModel);

    return modeModel;
}
