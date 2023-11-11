#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr, const int value = 0);
    void dec();
    QString as_string();
    void set_value(const int value);
private:
    int value;

signals:
    void change_state();
};

#endif // STOPWATCH_H
