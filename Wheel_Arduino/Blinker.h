#ifndef BLINKER_H
#define BLINKER_H

#include "Arduino.h"
#include "Task.h"

//Simple blinker class which allows to blink an LED

class Blinker : public Task
{
public:
  Blinker() {return;};
  Blinker(uint8_t);
  virtual bool run(); //Overriding run method from TimedTask

private:
  uint8_t pin;
  bool on;
};

#endif
