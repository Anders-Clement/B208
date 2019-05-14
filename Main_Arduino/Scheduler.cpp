
#include "Scheduler.h"
#include "Arduino.h"

//Implementation of Scheduler class

Scheduler::Scheduler(Task** _tasks, uint8_t _numOfTasks) : tasks(_tasks), numOfTasks(_numOfTasks)
{
}

void Scheduler::run()
{
  while(true) //Never stop running tasks
  {
    Task** tpp = tasks;
    uint32_t now = millis();
    for(uint8_t i = 0; i < numOfTasks; i++)
    {
      Task* tp = *tpp;
      if(tp->canRun(now))
      {
        tp->run(now);
        //break; //break to ensure prioritization, can be removed if prioritazation is not required.
      }
      tpp++;
    }
  }
}
