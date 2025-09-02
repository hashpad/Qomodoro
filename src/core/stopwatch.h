#pragma once
#include <QObject>
#include <QSoundEffect>

class Stopwatch : public QObject {
  Q_OBJECT
public:
  explicit Stopwatch(QObject *parent = nullptr, int value = 0);
  ~Stopwatch() override = default;

  void set_ticking_enabled(bool enabled);
  // Decrement stopwatch until it reaches 0, then emit signal to change state
  void dec();
  // Get stopwatch value in the form mm:ss
  QString as_string() const;
  // Set stopwatch value, it also sets the "save" value
  void set_goal(int value);
  // Get current stopwatch value
  int get_value() const;
  // Get starting stopwatch value
  int get_save() const;
  // Reset to saved value
  void reset();


private:
  bool ticking_enabled = true;
  // Stopwatch current value in seconds
  int value = 0;
  // Stopwatch starting value in seconds
  int save = 0;
  // Ticking sound effect
  QSoundEffect* tickEffect = nullptr;

signals:
  // Used to publish that the stopwatch has reached 0
  void change_state();
};
