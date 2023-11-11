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

private:
    QSqlDatabase m_db;
signals:
};

#endif // DATABASE_H
