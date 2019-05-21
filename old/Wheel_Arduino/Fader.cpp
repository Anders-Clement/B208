#include "Fader.h"
#include "Arduino.h"

//Implementation of Fader class

Fader::Fader(float _steps, uint8_t _pin) : pin(_pin)
{
  pinMode(pin, OUTPUT);
  stepSize = 255/_steps;
  level = 0;
}

bool Fader::run()
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
  return true;
}
