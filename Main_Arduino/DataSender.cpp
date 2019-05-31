#include "DataSender.h"

DataSender::DataSender(int* _pins, uint32_t _now, uint32_t _rate) : TimedTask(_now, _rate), pins(_pins)
{
  for(int i = 0; i < 5; i++)  
    pinMode(pins[i],INPUT);
  //last pin is a button, use PULL_UP:
  pinMode(pins[5], INPUT_PULLUP);
}


void DataSender::run(uint32_t now)  //reads from the pins, and sends the data to the pc
{
  msg=""; //string for storing the message to be sent
  msg+="#"; //add the starting '#'
  for(int i=0; i<2 ;i++)  //read the two analog values (the potentiometers) and add them to the message:
  {
  msg+=analogRead(pins[i]);
  msg+=",";
  }
  for(int i=2; i<5 ;i++)  //now read the 3 pins from the switch:
  {
  msg+=digitalRead(pins[i]);
  msg+=",";
  }
   msg+=!digitalRead(pins[5]); //and finally check if the reset button is pushed:
  msg+=",";
  msg+="!";
  Serial.print(msg);  //msg is constructed, send it
  incRunTime(rate); //incRunTime so it runs at wanted rate
}
