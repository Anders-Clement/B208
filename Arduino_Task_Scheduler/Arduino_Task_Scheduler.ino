

#include "Scheduler.h"    //Scheduler class which runs tasks
#include "Blinker.h"  //Derived from TimedTask, blinks an LED
#include "Fader.h"  //Derived from TimedTask, fades an LED up and down


void setup() {
}

void loop() {
  
  uint32_t now = millis();    //Get current time, it is needed to construct the tasks:
  Blinker blink(5, now, 1000);  //Blinker task, LED on pin 5, blink every 1000ms
  Fader fader(now, 1000, 20, 9);  //Fader task, fade up/down every 1000ms in 20 steps, in pin 9
  Task* tasks[] = {&blink, &fader}; //Add all tasks to an array, to feed to the scheduler 
                                    //More can be easily be added, as long as they inherit from Task

  Scheduler sched(tasks, sizeof(tasks)/sizeof(tasks[0])); //Constructing our scheduler. 
                                                          //It needs a pointer to an array of Task objects,
                                                          //and the amount of tasks to run (which is calculated from sizeof()

  sched.run();  //Runs the scheduler, which runs the task. It never returns
}
