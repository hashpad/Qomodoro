#include "stopwatch.h"

void Stopwatch::set_ticking_enabled(bool enabled) {
  ticking_enabled = enabled;
}

Stopwatch::Stopwatch(QObject *parent, int value)
  : QObject{parent}, value(value), save(value) {
  tickEffect = new QSoundEffect(this);
  tickEffect->setSource(QUrl::fromLocalFile("resources/tick.wav"));
  tickEffect->setVolume(0.25f); // Adjust volume as needed
}



void Stopwatch::dec() {
  if (value > 0) {
    --value;
    if (ticking_enabled && tickEffect && tickEffect->isLoaded()) {
      tickEffect->play();
    }
  } else {
    emit change_state();
  }
}


QString Stopwatch::as_string() const {
  QString minutes = QString::number(value / 60).rightJustified(2, '0');
  QString seconds = QString::number(value % 60).rightJustified(2, '0');
  return minutes + ":" + seconds;
}


void Stopwatch::set_goal(int value) { save = value; }
int Stopwatch::get_value() const { return value; }
int Stopwatch::get_save() const { return save; }
void Stopwatch::reset() { value = save; }
