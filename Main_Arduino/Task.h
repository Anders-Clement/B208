
#ifndef TASK_H
#define TASK_H

//Task class definition, virtual method means the method must be defined by a class which inherits from class

#include "stdint.h"

class Task
{
public:
  virtual bool canRun(uint32_t now) = 0;
  virtual void run(uint32_t now) = 0;
  
};

//TimedTask inherits from Task, and is made to run at a specified interval

class TimedTask : public Task
{
public:
  TimedTask(uint32_t _now, uint32_t _rate);
  virtual bool canRun(uint32_t now);
  virtual void run(uint32_t now) =0;
  void incRunTime(uint32_t _rate);  //method to increment the runtime (next point in time at which the task can run)
  uint32_t rate;

private:
  uint32_t runTime;
  
};

#endif
