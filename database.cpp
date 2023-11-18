#include "database.h"

#include <QDebug>
#include <QApplication>
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
        if(!this->get_pomodoros(QDate::currentDate())) if(!this->init()) QApplication::quit();
    }
}

bool Database::init() {
    QSqlQuery query;
    query.prepare("CREATE TABLE pomodoros(ids integer primary key, duration integer, date DATE);");
    if(!query.exec()) return false;

    query.prepare("CREATE TABLE breaks(ids integer primary key, duration integer, date DATE);");
    if(!query.exec()) return false;

    QString query_str;
    query_str = "CREATE TABLE config" \
        "(ids integer primary key," \
        " duration integer," \
        " break_duration integer," \
        " long_break_duration integer," \
        " pomodoros_b4_long_break integer," \
        " ticking_sound number(1)," \
        " notify number(1)," \
        " start_break_sound nvarchar(255)," \
        " end_break_sound nvarchar(255)," \
        " hide_other_notifications number(1))";

    query.prepare(query_str);
    if(!query.exec()) return false;

    return true;
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

bool Database::prepare_config() {

    QSqlQuery query;
    QString into("duration, ");
    into.append("break_duration, ");
    into.append("long_break_duration, ");
    into.append("pomodoros_b4_long_break, ");
    into.append("ticking_sound, ");
    into.append("notify, ");
    // into.append("start_break_sound, ");
    // into.append("end_break_sound, ");
    into.append("hide_other_notifications");

    query.prepare("INSERT INTO config ("+into+") VALUES (1500, 300, 600, 5, 0, 1, 0)");
    if(query.exec()) return true;
    else qInfo() << query.lastError();
    return false;
}
bool Database::set_pm_duration(int duration) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET duration = (:duration) WHERE ids= 1");
          query.bindValue(":duration", duration);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}

int Database::get_pm_duration() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_pm_duration();
        } else {
          int ret = query.record().value("duration").toInt();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return false;
}

bool Database::set_break_duration(int duration) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET break_duration = (:duration) WHERE ids= 1");
          query.bindValue(":duration", duration);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}

int Database::get_break_duration() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_break_duration();
        } else {
          int ret = query.record().value("break_duration").toInt();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return false;
}

bool Database::set_long_break_duration(int duration) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET long_break_duration = (:duration) WHERE ids= 1");
          query.bindValue(":duration", duration);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}


int Database::get_long_break_duration() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_long_break_duration();
        } else {
          int ret = query.record().value("long_break_duration").toInt();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return false;
}
int Database::get_cycles() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_cycles();
        } else {
          int ret = query.record().value("pomodoros_b4_long_break").toInt();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return false;
}

bool Database::set_cycles(int cycles) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET pomodoros_b4_long_break = (:cycles) WHERE ids= 1");
          query.bindValue(":cycles", cycles);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}

int Database::get_ticking_sound() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_cycles();
        } else {
          int ret = query.record().value("ticking_sound").toInt();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return false;
}

bool Database::set_ticking_sound(int value) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET ticking_sound = (:value) WHERE ids= 1");
          query.bindValue(":value", value);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}

int Database::get_notify() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_notify();
        } else {
          int ret = query.record().value("notify").toInt();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return false;
}

bool Database::set_notify(int value) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET notify = (:value) WHERE ids= 1");
          query.bindValue(":value", value);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}


QString Database::get_start_break_sound() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_start_break_sound();
        } else {
          QString ret = query.record().value("start_break_sound").toString();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return "";
}

bool Database::set_start_break_sound(QString value) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET start_break_sound = (:value) WHERE ids= 1");
          query.bindValue(":value", value);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}

QString Database::get_end_break_sound() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_end_break_sound();
        } else {
          QString ret = query.record().value("end_break_sound").toString();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return "";
}

bool Database::set_end_break_sound(QString value) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET end_break_sound = (:value) WHERE ids= 1");
          query.bindValue(":value", value);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}


int Database::get_hide_other_notifications() {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids= 1");
    if(query.exec()) {
        if(!query.first()) {
            prepare_config();
            return get_hide_other_notifications();
        } else {
          int ret = query.record().value("hide_other_notifications").toInt();
          return ret;
        }
  }
    else {
        qInfo() << "Error:" << query.lastError();
    }
    return false;
}

bool Database::set_hide_other_notifications(int value) {
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ids = 1");
    if(query.exec()) {
        if(query.first()) {
          query.prepare("UPDATE config SET hide_other_notifications = (:value) WHERE ids= 1");
          query.bindValue(":value", value);
          if(query.exec()) return true;
          else qInfo() << "Error" << query.lastError();
        }
    }
    else qInfo() << "Error" << query.lastError();
    return false;
}
