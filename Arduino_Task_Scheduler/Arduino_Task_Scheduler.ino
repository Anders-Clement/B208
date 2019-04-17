#include "Scheduler.h"    //Scheduler class which runs tasks
#include "Blinker.h"  //Derived from TimedTask, blinks an LED
#include "Fader.h"  //Derived from TimedTask, fades an LED up and down

Scheduler *taskManager;  // Creating a taskManager to run things at times
Blinker *blink;   // A led blinker on pin 13
Fader *fader; // Making a fader object which increments 20 at a time on pin 9

void setup() {
  Serial.begin(115200);
  while(!Serial)
  {
    delay(1);
  }
  Serial.println("Begin");
  
  taskManager = new Scheduler();
  blink = new Blinker(13);
  fader = new Fader(20, 9);

  taskManager->registerTask(fader, 1500); //Adds the fader object to the timer, and runs once a second
  taskManager->registerTask(blink, 2000); //Adds the blinker class which runs ever 2 second
}

void loop() {
  taskManager->update();  //Runs the scheduler, which runs the task.
}
