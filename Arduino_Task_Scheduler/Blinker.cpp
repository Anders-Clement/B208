#include "Blinker.h"

//Implementation of Blinker class

Blinker::Blinker(uint8_t _pin) : pin(_pin)
{
  pinMode(pin, OUTPUT);
}

bool Blinker::run()
{
  if(on)
  {
    on = false;
  }
  else
  {
    on = true;
  }
  digitalWrite(pin, on);
  return true;
}
