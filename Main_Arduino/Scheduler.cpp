
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
    Task** tpp = tasks; //tpp is a copy of the array of tasks
    uint32_t now = millis();  //get current time
    for(uint8_t i = 0; i < numOfTasks; i++) //loop through all tasks. If it can run, then run it
    {
      Task* tp = *tpp;  //dereference tpp, to get a pointer to a task (tp)
      if(tp->canRun(now)) //can tp run? if tp->canRun(now) returns true, then it should be run
      {
        tp->run(now);
        //break; //break to ensure prioritization, can be removed if prioritazation is not required.
      }
      tpp++;  //increment tpp to point to the next task in the array of tasks
    }
  }
}
