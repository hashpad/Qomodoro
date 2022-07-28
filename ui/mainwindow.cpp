#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , pomodoroModel(new Pomodoro(false, new FocusState(new Timer(2, 0))))

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
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getActiveState()->getTimer()->getLeftString()));




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
        this->pomodoroModel->setQTimer(new QTimer(this));
        connect(this->pomodoroModel->getQTimer(), &QTimer::timeout, this, &MainWindow::incrementTimer);
        this->pomodoroModel->getQTimer()->start(1000);
    }else {
        ui->startPauseBtn->setIcon(QIcon::fromTheme("media-playback-start"));
        this->pomodoroModel->setIsRunning(false);
        this->pomodoroModel->getQTimer()->stop();
        delete this->pomodoroModel->getQTimer();
    }
}

void MainWindow::incrementTimer() {

    this->pomodoroModel->getActiveState()->increment();
    update_leftLabel();
}


void MainWindow::on_stopBtnClicked()
{
    if(this->pomodoroModel->getIsRunning()) {
        on_startPauseBtnClicked();
        this->pomodoroModel->getActiveState()->getTimer()->reset();
    }
    else {
        this->pomodoroModel->getActiveState()->getTimer()->reset();
    }
    update_leftLabel();
}


void MainWindow::update_leftLabel() {
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getActiveState()->getTimer()->getLeftString()));
}
void MainWindow::on_leftValueUpdate() {
    ui->leftTimeLbl->setText(QString::fromStdString(this->pomodoroModel->getActiveState()->getTimer()->getLeftString()));
}

void MainWindow::on_settingsBtnClicked()
{
    pref->show();
}


QStringListModel* MainWindow::createModeComboModel() {
    QStringList* modeComboModel = new QStringList();
    *modeComboModel << QString::fromStdString(FocusState::getStaticName());
    *modeComboModel << QString::fromStdString(ShortBreakState::getStaticName());
    *modeComboModel << QString::fromStdString(LongBreakState::getStaticName());

    QStringListModel* modeModel = new QStringListModel(this);
    modeModel->setStringList(*modeComboModel);

    return modeModel;
}
