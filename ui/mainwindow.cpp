#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMediaPlayer>
#include <QAudioOutput>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    // external models
    , pomodoroModel(new Pomodoro(this))

    // ui elements
    , ui(new Ui::MainWindow)
    , pref(new Preferences(this, pomodoroModel))

    // qt models
    , modeComboModel(createModeComboModel())
    , mediaPlayer(new QMediaPlayer(this))
{
    qDebug() << "passed main constructor",
    ui->setupUi(this);
    qDebug() << "setup main ui",

    settings.beginGroup("MainWindow");


    pomodoroModel->setPomodoroDuration(settings.value("pomodoro_duration", 25).toInt() * 60);
    pomodoroModel->setShortBreakDuration(settings.value("short_break_duration", 5).toInt() * 60);
    pomodoroModel->setLongBreakDuration(settings.value("long_break_duration", 30).toInt() * 60);

    qDebug() << "Pomodoro duration loaded",
    qDebug() <<  pomodoroModel->getPomodoroDuration();


    pomodoroModel->setActiveState(new FocusState());

    qDebug() <<  "focus state set";

//    QBarSet *set0 = new QBarSet("today");

//    *set0 << 39 << 5;

//    QBarSeries *series = new QBarSeries(ui->chartView);
//    series->append(set0);

//    QChart *chart = new QChart();
//    chart->addSeries(series);
//    chart->setAnimationOptions(QChart::SeriesAnimations);
//    QStringList categories;
//    categories << "Pomodoro" << "Break";
//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
//    chart->addAxis(axisX, Qt::AlignBottom);
//    series->attachAxis(axisX);

//    QValueAxis *axisY = new QValueAxis();
//    chart->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisY);

//    chart->legend()->setVisible(false);

//    ui->chartView->setChart(chart);
//    ui->chartView->setRenderHint(QPainter::Antialiasing);

    ui->modeCombo->setModel(modeComboModel);
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getActiveState()->getTimer()->getLeftString()));



    connect(pref, &Preferences::leftValueUpdate, this, &MainWindow::on_leftValueUpdate);


    connect(this->ui->startPauseBtn, &QPushButton::clicked, this, &MainWindow::on_startPauseBtnClicked);

    connect(this->ui->stopBtn, &QPushButton::clicked, this, &MainWindow::on_stopBtnClicked);
    connect(this->ui->settingsBtn, &QPushButton::clicked, this, &MainWindow::on_settingsBtnClicked);
    connect(this->ui->modeCombo, &QComboBox::currentTextChanged, this, &MainWindow::on_modeComboCurrentTextChanged);

    connect(pomodoroModel, &Pomodoro::stateChange, this, &MainWindow::modeChange);

    connect(pomodoroModel, &Pomodoro::stateDone, this, &MainWindow::modeDone);
}

MainWindow::~MainWindow()
{
    delete pref;
    delete pomodoroModel;
    delete ui;
}

void MainWindow::triggerNotification()
{
    /* TODO: implement systray icon notification (maybe over dbus?) */
    this->show();
    this->raise();
    this->activateWindow();
}

void MainWindow::startPomodoro() {
    if(!this->pomodoroModel->getIsRunning()) {
        ui->startPauseBtn->setIcon(QIcon::fromTheme("media-playback-pause"));
        this->pomodoroModel->setIsRunning(true);
        this->pomodoroModel->setQTimer(new QTimer(this));
        connect(this->pomodoroModel->getQTimer(), &QTimer::timeout, this, &MainWindow::incrementTimer);
        this->pomodoroModel->getQTimer()->start(1000);
    }
}
void MainWindow::pausePomodoro() {
    if(this->pomodoroModel->getIsRunning()) {
        ui->startPauseBtn->setIcon(QIcon::fromTheme("media-playback-start"));
        this->pomodoroModel->setIsRunning(false);
        this->pomodoroModel->getQTimer()->stop();
        delete this->pomodoroModel->getQTimer();
    }
}
void MainWindow::stopPomodoro() {
    if(this->pomodoroModel->getIsRunning()) {
        on_startPauseBtnClicked();
        this->pomodoroModel->getActiveState()->getTimer()->reset();
    }
    else {
        this->pomodoroModel->getActiveState()->getTimer()->reset();
    }
    update_leftLabel();
}

void MainWindow::on_startPauseBtnClicked()
{
    if(!this->pomodoroModel->getIsRunning())
      startPomodoro();
    else
      pausePomodoro();
}

void MainWindow::incrementTimer() {

    this->pomodoroModel->getActiveState()->increment();
    update_leftLabel();
}


void MainWindow::on_stopBtnClicked()
{
    this->stopPomodoro();
}


void MainWindow::update_leftLabel() {
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getActiveState()->getTimer()->getLeftString()));
}
void MainWindow::update_modeCombo() {
    ui->modeCombo->blockSignals(true);
    ui->modeCombo->setCurrentText(QString::fromStdString(this->pomodoroModel->getActiveState()->getName()));
    ui->modeCombo->blockSignals(false);
}
void MainWindow::on_leftValueUpdate() {
    update_leftLabel();
}

void MainWindow::on_settingsBtnClicked()
{
    pref->show();
}


QStringListModel* MainWindow::createModeComboModel() {
    QStringList modeComboModel = QStringList();
    modeComboModel << QString::fromStdString(FocusState::getStaticName());
    modeComboModel << QString::fromStdString(ShortBreakState::getStaticName());
    modeComboModel << QString::fromStdString(LongBreakState::getStaticName());

    QStringListModel* modeModel = new QStringListModel(this);
    modeModel->setStringList(modeComboModel);

    return modeModel;
}

void MainWindow::on_modeComboCurrentTextChanged(const QString &state)
{
    if(state == QString::fromStdString(ShortBreakState::getStaticName())) {
        pomodoroModel->setActiveState(new ShortBreakState());
        qDebug() <<  "Short break set";
        qDebug() <<  pomodoroModel->getShortBreakDuration();
        qDebug() <<  QString::fromStdString(pomodoroModel->getActiveState()->getTimer()->getLeftString());
    }
    else if(state == QString::fromStdString(LongBreakState::getStaticName()))
        pomodoroModel->setActiveState(new LongBreakState());
    else
        pomodoroModel->setActiveState(new FocusState());
}
void MainWindow::startMedia(int playFor) {
    mediaQtimer = new QTimer(this);
    mediaPlayer->setAudioOutput(new QAudioOutput(this));
    mediaPlayer->setSource(QUrl::fromLocalFile("/home/aosome/QTResources/pomodoro_done.mp3"));

    mediaQtimer->start(playFor);

    mediaPlayer->play();

    connect(this->mediaQtimer, &QTimer::timeout, this, &MainWindow::stopMedia);
}

void MainWindow::stopMedia() {
    mediaPlayer->stop();
    delete mediaPlayer->audioOutput();

    mediaQtimer->stop();
    delete mediaQtimer;
}

void MainWindow::modeDone() {
    modeChange();
    triggerNotification();
    startMedia(10000); // play media for x ms
}
void MainWindow::modeChange() {
    update_modeCombo();
    update_leftLabel();
}

void MainWindow::exit() {
    settings.endGroup();
}
