
#include "Task.h"

//Simple blinker class which allows to blink an LED

class Blinker : public TimedTask
{
public:
  Blinker(*Serial serial, uint8_t _pin, uint32_t _now, uint32_t _rate);
  void run(uint32_t now); //Overriding run method from TimedTask

private:
  uint8_t pin;
  bool on;
};
