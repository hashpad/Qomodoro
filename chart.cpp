#include "chart.h"


Chart::Chart(QObject *parent, Database* db)
    : QObject{parent}, db(db), day_offset(0), week_offset(0), month_offset(0)
{
}

QChart *Chart::get_day_view_chart() {
    int today_breaks = db->get_breaks(QDate::currentDate().addDays(day_offset)) / 60;
    int today_pomodoros = db->get_pomodoros(QDate::currentDate().addDays(day_offset)) / 60;

    QBarSet *set0 = new QBarSet("Value");

    *set0 << today_pomodoros << today_breaks;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "Pomodoro" << "Break";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,qMax(today_pomodoros + (10 - (today_pomodoros % 10)) ,today_breaks + (10 - (today_breaks % 10))));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    return chart;
}
QChart *Chart::get_week_view_chart() {
    int day_of_week = QDate::currentDate().dayOfWeek() - 7 * week_offset;

    QBarSet *set0 = new QBarSet("Pomodoro");
    QBarSet *set1 = new QBarSet("Break");

    for(int day_i = 1; day_i <= 7; ++day_i){
      *set0
          << db->get_pomodoros(QDate::currentDate().addDays(-day_of_week + day_i)) / 60;
      *set1
          << db->get_breaks(QDate::currentDate().addDays(-day_of_week + day_i)) / 60;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "Mon" << "Tue" << "Wed" << "Thu" << "Fri" << "Sat" << "Sun";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    int max_value = 0;
    for (int i = 0; i < set0->count(); ++i) {
        max_value = max_value >= set0->at(i) ? max_value : set0->at(i);
        max_value = max_value >= set1->at(i) ? max_value : set1->at(i);
    }

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, max_value + (10 - (max_value % 10)));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    return chart;
}

QChart *Chart::get_month_view_chart() {
    QDate from = QDate::currentDate().addMonths(month_offset).addDays(1 - QDate::currentDate().addMonths(month_offset).day());


    QStringList categories;
    QBarSet *set0 = new QBarSet("Pomodoro");
    QBarSet *set1 = new QBarSet("Break");
    for(int i = 0; i < from.daysInMonth(); ++i) {
      *set0
          << db->get_pomodoros(from.addDays(i)) / 60;
      *set1
          << db->get_breaks(from.addDays(i)) / 60;
      categories << QString::number(i+1);
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    int max_value = 0;
    for (int i = 0; i < set0->count(); ++i) {
        max_value = max_value >= set0->at(i) ? max_value : set0->at(i);
        max_value = max_value >= set1->at(i) ? max_value : set1->at(i);
    }

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, max_value + (10 - (max_value % 10)));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    return chart;
}

Chart::~Chart()
{
    delete chart;
}

int Chart::get_day_offset() { return this->day_offset; }
int Chart::get_week_offset() { return this->week_offset; }
int Chart::get_month_offset() { return this->month_offset; }

void Chart::set_day_offset(int offset) { this->day_offset = offset; }
void Chart::set_week_offset(int offset) { this->week_offset = offset; }
void Chart::set_month_offset(int offset) { this->month_offset = offset; }

QString Chart::get_day_name() {
    if(day_offset == 0) return QString("Today");
    if(day_offset == -1) return QString("Yesterday");
    return QDate::currentDate().addDays(day_offset).toString();
}

QString Chart::get_week_name() {
    if(week_offset == 0) return QString("This week");
    int day_of_week = QDate::currentDate().dayOfWeek() - 7 * week_offset;
    QString ret;
    ret.append(QDate::currentDate().addDays(-day_of_week + 1).toString());
    ret.append(" to ");
    ret.append(QDate::currentDate().addDays(-day_of_week + 7).toString());
    qInfo() << ret;
    return ret;
}
QString Chart::get_month_name() {
    QDate from = QDate::currentDate().addMonths(month_offset).addDays(1 - QDate::currentDate().addMonths(month_offset).day());
    return from.toString();
}
