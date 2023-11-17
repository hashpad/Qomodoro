#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr, const QString &path = "");
    bool add_pomodoro(int duration, QDate day);
    bool add_break(int duration, QDate day);
    bool add(int duration, QDate day, QString &type);
    bool set_pm_duration(int duration);
    int get_pm_duration();
    bool set_break_duration(int duration);
    int get_break_duration();
    bool set_long_break_duration(int duration);
    int get_long_break_duration();
    bool set_cycles(int cycles);
    int get_cycles();
    bool set_ticking_sound(int value);
    int get_ticking_sound();
    int get_breaks(QDate day);
    int get_pomodoros(QDate day);
    bool prepare_config();

private:
    QSqlDatabase m_db;
signals:
};

#endif // DATABASE_H
