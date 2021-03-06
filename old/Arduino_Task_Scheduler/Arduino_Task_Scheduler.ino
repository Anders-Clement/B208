#include "Scheduler.h"    //Scheduler class which runs tasks
#include "FastLED.h"

#define NUM_LEDS 9
#define LED_PIN 4

CRGB leds[NUM_LEDS];


void setup() {
         FastLED.addLeds<WS2811, LED_PIN>(leds, NUM_LEDS);
         for(int i = 0; i < NUM_LEDS; i++)
         {
          leds[i] = CRGB::Red;
         }
         FastLED.show();
}

void loop() {



  
  uint32_t now = millis();    //Get current time, it is needed to construct the tasks:
  Task* tasks[] = {}; //Add all tasks to an array, to feed to the scheduler 
  //More can be easily be added, as long as they inherit from Task

  Scheduler sched(tasks, sizeof(tasks)/sizeof(tasks[0])); //Constructing our scheduler. 
                                                          //It needs a pointer to an array of Task objects,
                                                          //and the amount of tasks to run (which is calculated from sizeof()

  sched.run();  //Runs the scheduler, which runs the task. It never returns
}
