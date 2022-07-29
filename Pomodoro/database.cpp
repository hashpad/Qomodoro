#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>

Database::Database(QObject *parent)
    : QObject{parent},
    sqlDB(QSqlDatabase::addDatabase("QSQLITE"))
{
    sqlDB.setDatabaseName("/home/aosome/.config/Qomodoro/stats.db");
    prepareDB();
}

void Database::prepareDB(){
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "CREATE TABLE IF NOT EXISTS stats ("
                    << "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    << "date DATE NOT NULL,"
                    << "pomodoro INT(255) DEFAULT NULL,"
                    << "break INT(255) DEFAULT NULL"
                    << ");";
    databaseQuery.exec(statement);
    sqlDB.close();
}

void Database::insertPomodoro(QDate date, int length)
{
    qDebug() << "db insert pomodoro called";
    if(dateExists(date) != 0) {
        qDebug() << "found";
        updatePomodoro(date, length);
        return;
    }
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "INSERT INTO stats"
                    << "(date, pomodoro, break)"
                    << " VALUES "
                    << "(:date, :pomodoro, 0)"
                    << ";";
    databaseQuery.prepare(statement);
    databaseQuery.bindValue(":date", date);
    databaseQuery.bindValue(":pomodoro", length);
    databaseQuery.exec();
    sqlDB.close();
}

int Database::getPomodoro(QDate date)
{
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "SELECT pomodoro FROM stats where date=(:date)";
    databaseQuery.prepare(statement);
    databaseQuery.bindValue(":date", date);
    databaseQuery.exec();
    int value = 0;
    if(databaseQuery.next()) {
        value = databaseQuery.value(0).toInt();
    }
    sqlDB.close();
    return value;
}

void Database::updatePomodoro(QDate date, int length)
{
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "UPDATE stats SET pomodoro=pomodoro + (:length) WHERE date=(:date)";
    databaseQuery.prepare(statement);
    databaseQuery.bindValue(":date", date);
    databaseQuery.bindValue(":length", length);
    databaseQuery.exec();
    sqlDB.close();
}
void Database::insertBreak(QDate date, int length)
{
    qDebug() << "db insert break called";
    if(dateExists(date) != 0) {
        updateBreak(date, length);
        return;
    }
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "INSERT INTO stats"
                    << "(date, pomodoro, break)"
                    << " VALUES "
                    << "(:date, 0, :break)"
                    << ";";
    databaseQuery.prepare(statement);
    databaseQuery.bindValue(":date", date);
    databaseQuery.bindValue(":break", length);
    databaseQuery.exec();
    sqlDB.close();
}


int Database::getBreak(QDate date)
{
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "SELECT break FROM stats where date=(:date)";
    databaseQuery.prepare(statement);
    databaseQuery.bindValue(":date", date);
    databaseQuery.exec();
    int value = 0;
    if(databaseQuery.next()) {
        value = databaseQuery.value(0).toInt();
    }
    sqlDB.close();
    return value;
}


void Database::updateBreak(QDate date, int length)
{
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "UPDATE stats SET break=break + (:length) WHERE date=(:date)";
    databaseQuery.prepare(statement);
    databaseQuery.bindValue(":date", date);
    databaseQuery.bindValue(":length", length);
    databaseQuery.exec();
    sqlDB.close();
}

bool Database::dateExists(QDate date) {
    sqlDB.open();
    QSqlQuery databaseQuery(sqlDB);
    QString statement;
    QTextStream statementStream(&statement);
    statementStream << "SELECT * FROM stats where date=(:date)";
    databaseQuery.prepare(statement);
    databaseQuery.bindValue(":date", date);
    databaseQuery.exec();
    bool exists = false;
    while(databaseQuery.next())
        exists = true;
    sqlDB.close();
    qDebug() << databaseQuery.size();
    return exists;
}
