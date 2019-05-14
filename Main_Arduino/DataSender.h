#include "Task.h"
#include "Arduino.h"

class DataSender : public TimedTask
{
    String  msg;
    int* pins;
  public:
    DataSender(int* _pins, uint32_t _now, uint32_t _rate);
    void run(uint32_t now);

};
