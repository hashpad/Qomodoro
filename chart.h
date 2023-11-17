#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QDate>
#include <QtCharts>
#include "database.h"

class Chart : public QObject
{
    Q_OBJECT
public:
    explicit Chart(QObject *parent = nullptr, Database* db = nullptr);
    ~Chart();
    QChart* get_day_view_chart();
    QChart* get_week_view_chart();
    QChart* get_month_view_chart();

    int get_day_offset();
    int get_week_offset();
    int get_month_offset();


    void set_day_offset(int offset);
    void set_week_offset(int offset);
    void set_month_offset(int offset);

    QString get_day_name();
    QString get_week_name();
    QString get_month_name();

private:
    QChart* chart;
    Database* db;
    int day_offset;
    int week_offset;
    int month_offset;
signals:
};

#endif // CHART_H
