#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QDate>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    void prepareDB();

    int getPomodoro(QDate date);
    int getBreak(QDate date);

    bool dateExists(QDate date);

private:
    void updatePomodoro(QDate date, int length);
    void updateBreak(QDate date, int length);
public slots:
    void insertPomodoro(QDate date, int length);
    void insertBreak(QDate date, int length);

private:
    QSqlDatabase sqlDB;
};

#endif // DATABASE_H
