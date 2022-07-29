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
    prepareDB();
}

bool Database::prepareDB(){
    sqlDB.setDatabaseName("/home/aosome/.config/Qomodoro/stats.db");
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
    qDebug() << databaseQuery.lastError().text();
    sqlDB.close();
    return true;
}

bool Database::insertPomodoro(QDate date, int length)
{
    return true;
}

bool Database::insertBreak(QDate date, int length)
{

    return true;
}

bool Database::getPomodoro(QDate date)
{

    return true;
}

bool Database::getBreak(QDate date)
{

    return true;
}
