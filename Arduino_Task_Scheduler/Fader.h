
#include "Task.h"

//Simple class to fade an LED up and down

class Fader : public TimedTask
{
public:
  Fader(uint32_t _now, float _rate, float _steps, uint8_t _pin);
  void run(uint32_t now);

private:
  uint8_t pin;
  float stepSize;
  float level;
};
