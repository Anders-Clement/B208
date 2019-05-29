
#include "Task.h"
#include "FastLED.h"


class DataReceiver : public Task
{
  CRGB* leds;
  int led_pin;
  

  public:
    DataReceiver(uint8_t _led_pin, CRGB* _leds, uint32_t _now);
    void run(uint32_t now);
    bool canRun(uint32_t now);
};
