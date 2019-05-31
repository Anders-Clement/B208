#include "Scheduler.h"    //Scheduler class which runs tasks
#include "DataSender.h"
#include "DataReceiver.h"
#include "FastLED.h"

#define NUM_LEDS 9  //9 leds on LED strip
#define LED_PIN 5 //LED on D5 pin

CRGB leds[NUM_LEDS];  //Creatign CRGB objects(they hold r,g,b values for each LED) and storing them in an array


void setup() {
         FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);  //Setting up FastLED
         Serial.begin(38400); 
         for(int i = 0; i < NUM_LEDS; i++)  //Setting all leds to black
         {
            leds[i].setRGB(0,0,0);
         }
         FastLED.show();  //This updates the LED's
}

void loop() {
  
  uint32_t now = millis();    //Get current time, it is needed to construct the tasks:

  int pins[] = {A0, A1, 9,10,11,12};  //Pins where we measure potentiometers and buttons
  DataSender ds(pins,now,50); //Datasender which reads from the pins, and sends it to the PC
  DataReceiver dr(3, leds, now);  //DataReciever which handles commands from the PC
  
  Task* tasks[] = {&ds, &dr}; //Add all tasks to an array, to feed to the scheduler 
  //More can be easily be added, as long as they inherit from Task

  Scheduler sched(tasks, sizeof(tasks)/sizeof(tasks[0])); //Constructing our scheduler. 
                                                          //It needs a pointer to an array of Task objects,
                                                          //and the amount of tasks to run (which is calculated from sizeof()
  sched.run();  //Runs the scheduler, which runs the task. It never returns
}
