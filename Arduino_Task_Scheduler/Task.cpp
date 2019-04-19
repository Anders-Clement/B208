
#include "Task.h"


 TimedTask::TimedTask(uint32_t _now, uint32_t _rate) : runTime(_now), rate(_rate)
 {
 }

bool TimedTask::canRun(uint32_t now)
{
  return now >= runTime;
}

void TimedTask::incRunTime(uint32_t rate)
{
  runTime += rate;
}
