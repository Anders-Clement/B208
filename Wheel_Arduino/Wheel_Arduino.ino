#include "Scheduler.h"    //Scheduler class which runs tasks
#include "Blinker.h"  //Derived from TimedTask, blinks an LED
#include "Fader.h"  //Derived from TimedTask, fades an LED up and down
#include "Talker.h" //For transmittion data to the master.
#include "IMUAngle.h" //Retriving the angle of the IMU.
#include "WheelLight.h"


Scheduler *taskManager;  // Creating a taskManager to run things at times
Blinker *blink;   // A led blinker on pin 13
Fader *fader; // Making a fader object which increments 20 at a time on pin 9
IMUAngle *angler; //Measures the angle from the IMU.
Transmitter *MhzTrans;
WheelLight *WheelLights;

void setup() {
  Serial.begin(9600);
  while(!Serial)
  {
    delay(1);
  }
  Serial.println("Begin");
  
  taskManager = new Scheduler();
  blink = new Blinker(13);
  angler = new IMUAngle();
  MhzTrans = new Transmitter(angler);
  WheelLights = new WheelLight(MhzTrans);

  taskManager->registerTask(blink, 1500); //Adds the blinker class which runs ever 2 second
  taskManager->registerTask(angler, 1000);
  taskManager->registerTask(MhzTrans, 1000);
  taskManager->registerTask(WheelLights, 1000);
}

void loop() {
  taskManager->update();  //Runs the scheduler, which runs the task.
}
