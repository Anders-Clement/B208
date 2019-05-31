
#include "Task.h"


 TimedTask::TimedTask(uint32_t _now, uint32_t _rate) : runTime(_now), rate(_rate)
 {
 }

bool TimedTask::canRun(uint32_t now)
{
  return now >= runTime;  //if current time is at or past runtime, which is the point at which the task should run, return true
}

void TimedTask::incRunTime(uint32_t rate)
{
  runTime += rate;  //add rate to runtime, such that it can run for every rate milliseconds
}
