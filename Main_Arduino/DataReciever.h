
#include "Task.h"
#include "FastLED.h"


class DataReciever : public Task
{
  CRGB* leds;
  int led_pin;
  

  public:
    DataReciever(uint8_t _led_pin, CRGB* _leds, uint32_t _now);
    void run(uint32_t now);
    bool DataReciever::canRun(uint32_t now);
};
