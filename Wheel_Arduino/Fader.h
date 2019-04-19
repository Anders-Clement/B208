#ifndef FADER_H
#define FADER_H

#include "Task.h"
#include "Arduino.h"

//Simple class to fade an LED up and down

class Fader : public Task
{
public:
  Fader() {return;};
  Fader(float _steps, uint8_t _pin);
  virtual bool run();

private:
  uint8_t pin;
  float stepSize;
  float level;
};

#endif
