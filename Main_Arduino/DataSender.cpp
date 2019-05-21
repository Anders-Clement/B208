#include "DataSender.h"

DataSender::DataSender(int* _pins, uint32_t _now, uint32_t _rate) : TimedTask(_now, _rate), pins(_pins)
{
  for(int i = 0; i < 5; i++)
    pinMode(pins[i],INPUT);
  //last pin is a button, use PULL_UP:
  pinMode(pins[5], INPUT_PULLUP);
}


void DataSender::run(uint32_t now)
{
  msg="";
  msg+="#";
  for(int i=0; i<2 ;i++)
  {
  msg+=analogRead(pins[i]);
  msg+=",";
  }
  for(int i=2; i<6 ;i++)
  {
  msg+=!digitalRead(pins[i]);
  msg+=",";
  }
  msg+="!";
  Serial.print(msg);
  incRunTime(rate);
}
