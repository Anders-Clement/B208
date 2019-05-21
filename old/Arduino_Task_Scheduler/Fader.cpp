#include "Fader.h"
#include "Arduino.h"

//Implementation of Fader class

Fader::Fader(uint32_t _now, float _rate, float _steps, uint8_t _pin) : TimedTask(_now, _rate/_steps), pin(_pin)
{
  pinMode(pin, OUTPUT);
  stepSize = 255/_steps;
  level = 0;
}

void Fader::run(uint32_t now)
{
  level += stepSize;
  if(level > 255)
  {
    level = 255;
    stepSize *= -1;
  }
  else if(level < 0)
  {
    level = 0;
    stepSize *= -1;
  }
  analogWrite(pin, level);
  incRunTime(rate);
}
