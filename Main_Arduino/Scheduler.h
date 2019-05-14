
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Task.h"

//Scheduler to run tasks

class Scheduler
{
public:
  Scheduler(Task** tasks, uint8_t _numOfTasks);
  void run();
private:
  Task** tasks;
  uint8_t numOfTasks;
};






#endif
