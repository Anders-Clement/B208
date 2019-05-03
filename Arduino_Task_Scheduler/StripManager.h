
#ifndef STRIPMANAGER_H
#define STRIPMANAGER_H

#include "Task.h"
#include "FastLED.h"

class StripManager : public TimedTask
{
public:
  StripManager(int _pin, uint32_t _now, uint32_t _rate, int _num_leds);
  void run(uint32_t now);

private:
  uint8_t pin;
  CRGB leds[];
  
};




#endif
