#include "StripManager.h"
#include "Arduino.h"
#include "FastLED.h"

//Implementation of Blinker class

StripManager::StripManager(int _pin, uint32_t _now, uint32_t _rate, int _num_leds) : TimedTask(_now, _rate), pin(_pin)
{
  CRGB leds[_num_leds];
  pinMode(_pin, OUTPUT);
  FastLED.addLeds<WS2811, pin>(leds, _num_leds);
  //FastLED.addLeds<WS2811, _pin>(leds, _num_leds);
}

void StripManager::run(uint32_t now)
{
  // Do stuff:


  FastLED.show();
  incRunTime(rate); 
}
