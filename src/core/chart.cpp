
#include "chart.h"
#include <qlogging.h>
#include <algorithm>


Chart::Chart(QObject *parent, Database *db)
  : QObject{parent}, db(db), day_offset(0), week_offset(0), month_offset(0) {}


namespace {
// Helper to round up to next multiple of 10
int roundUp10(int value) {
  if (value <= 0) return 10;
  return value + (10 - value % 10);
}
}

QChart *Chart::get_day_view_chart() {
  auto current_day = QDate::currentDate().addDays(day_offset);
  int today_breaks = db->get_breaks(current_day) / 60;
  int today_pomodoros = db->get_pomodoros(current_day) / 60;

  QBarSet *set = new QBarSet("Value", this);
  *set << today_pomodoros << today_breaks;

  QBarSeries *series = new QBarSeries(this);
  series->append(set);

  chart = new QChart();
  chart->addSeries(series);
  chart->setAnimationOptions(QChart::SeriesAnimations);

  QStringList categories{ "Pomodoro", "Break" };
  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  int maxY = std::max(roundUp10(today_pomodoros), roundUp10(today_breaks));
  QValueAxis *axisY = new QValueAxis();
  axisY->setRange(0, maxY);
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);
  return chart;
}

QChart *Chart::get_week_view_chart() {
  int day_of_week = QDate::currentDate().dayOfWeek() - 7 * week_offset;

  QBarSet *set_pomodoro = new QBarSet("Pomodoro");
  QBarSet *set_break = new QBarSet("Break");
  int max_value = 0;

  for (int day_i = 1; day_i <= 7; ++day_i) {
    int pomodoros = db->get_pomodoros(QDate::currentDate().addDays(-day_of_week + day_i)) / 60;
    int breaks = db->get_breaks(QDate::currentDate().addDays(-day_of_week + day_i)) / 60;
    *set_pomodoro << pomodoros;
    *set_break << breaks;
    max_value = std::max({max_value, pomodoros, breaks});
  }

  QBarSeries *series = new QBarSeries();
  series->append(set_pomodoro);
  series->append(set_break);

  chart = new QChart();
  chart->addSeries(series);
  chart->setAnimationOptions(QChart::SeriesAnimations);

  QStringList categories{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis *axisY = new QValueAxis();
  axisY->setRange(0, roundUp10(max_value));
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);
  return chart;
}


QChart *Chart::get_month_view_chart() {
  QDate base = QDate::currentDate().addMonths(month_offset);
  QDate from = base.addDays(1 - base.day());
  int days = from.daysInMonth();


  QStringList categories;
  QBarSet *set_pomodoro = new QBarSet("Pomodoro");
  QBarSet *set_break = new QBarSet("Break");
  int max_value = 0;

  for (int i = 0; i < days; ++i) {
    int pomodoros = db->get_pomodoros(from.addDays(i)) / 60;
    int breaks = db->get_breaks(from.addDays(i)) / 60;
    *set_pomodoro << pomodoros;
    *set_break << breaks;
    if (i == 0 || ((i + 1) % 5 == 0 && i != 0) || i == days - 1) {
      categories << QString::number(i + 1);
    }

    max_value = std::max({max_value, pomodoros, breaks});
  }

  QBarSeries *series = new QBarSeries();
  series->append(set_pomodoro);
  series->append(set_break);

  chart = new QChart();
  chart->addSeries(series);
  chart->setAnimationOptions(QChart::SeriesAnimations);


  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis *axisY = new QValueAxis();
  axisY->setRange(0, roundUp10(max_value));
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);
  return chart;
}


Chart::~Chart() = default;


int Chart::get_day_offset() const { return day_offset; }
int Chart::get_week_offset() const { return week_offset; }
int Chart::get_month_offset() const { return month_offset; }

void Chart::set_day_offset(int offset) { day_offset = offset; }
void Chart::set_week_offset(int offset) { week_offset = offset; }
void Chart::set_month_offset(int offset) { month_offset = offset; }


QString Chart::get_day_name() const {
  if (day_offset == 0)
    return QStringLiteral("Today");
  if (day_offset == -1)
    return QStringLiteral("Yesterday");
  return QDate::currentDate().addDays(day_offset).toString();
}


QString Chart::get_week_name() const {
  if (week_offset == 0)
    return QStringLiteral("This week");
  int day_of_week = QDate::currentDate().dayOfWeek() - 7 * week_offset;
  QString ret = QDate::currentDate().addDays(-day_of_week + 1).toString();
  ret.append(" to ");
  ret.append(QDate::currentDate().addDays(-day_of_week + 7).toString());
  qInfo() << ret;
  return ret;
}

QString Chart::get_month_name() const {
  QDate base = QDate::currentDate().addMonths(month_offset);
  QDate from = base.addDays(1 - base.day());
  return from.toString();
}
