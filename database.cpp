#include "database.h"

#include <QDebug>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
Database::Database(QObject *parent, const QString &path)
    : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()) {
        qInfo() << "Error: connection with db failed";
    } else {
        qInfo() << "db conn ok!";
    }
}



bool Database::add(int duration, QDate day, QString &type) {
    QSqlQuery query;
    query.prepare("SELECT * FROM " + type + " WHERE date = (:day)");
    query.bindValue(":day", day.toString());
    if(query.exec()) {
        if(query.next()) {
          int id = query.record().value("ids").toInt();
          int old_duration = query.record().value("duration").toInt();
          query.prepare("UPDATE " + type + " SET duration = (:duration) WHERE ids = (:id)");
          query.bindValue(":duration", old_duration + duration);
          query.bindValue(":id", id);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }else {
          query.prepare("INSERT INTO " + type + " (duration, date) VALUES (:duration, :day)");
          query.bindValue(":duration", duration);
          query.bindValue(":day", day.toString());
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}
bool Database::add_break(int duration, QDate day) {
    QString type("breaks");
    return this->add(duration, day, type);
}
bool Database::add_pomodoro(int duration, QDate day) {
    QString type("pomodoros");
    return this->add(duration, day, type);
}

int Database::get_breaks(QDate day) {
    QSqlQuery query;
    query.prepare("SELECT * FROM breaks WHERE date = (:day)");
    query.bindValue(":day", day.toString());
    if(query.exec()) {
        if(query.next()) {
            return query.record().value("duration").toInt();
        }else {
            return 0;
        }
    }else {
        qInfo() << "Error: " << query.lastError();
    }
    return 0;
}

int Database::get_pomodoros(QDate day) {
    QSqlQuery query;
    query.prepare("SELECT * FROM pomodoros WHERE date = (:day)");
    query.bindValue(":day", day.toString());
    if(query.exec()) {
        if(query.next()) {
            return query.record().value("duration").toInt();
        }else {
            return 0;
        }
    }else {
        qInfo() << "Error: " << query.lastError();
    }
    return 0;
}

bool Database::set_pm_duration(int duration) {

    return true;
}
