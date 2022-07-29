#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    bool prepareDB();

    bool insertPomodoro(QDate date, int length);
    bool insertBreak(QDate date, int length);

    bool getPomodoro(QDate date);
    bool getBreak(QDate date);
signals:
    void updateEntries();

private:
    QSqlDatabase sqlDB;
};

#endif // DATABASE_H
