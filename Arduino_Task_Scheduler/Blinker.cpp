
#include "Blinker.h"
#include "Arduino.h"

//Implementation of Blinker class

Blinker::Blinker(uint8_t _pin, uint32_t _now, uint32_t _rate) : TimedTask(_now, _rate), pin(_pin)
{
  pinMode(pin, OUTPUT);
}

void Blinker::run(uint32_t now)
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
  incRunTime(rate); 
}
