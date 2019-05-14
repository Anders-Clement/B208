


#include "aRead.h"
#include "Arduino.h"

  void AnaRead::addReadPin(int pin)
  {
    pins[numOfPins] = pin;
    numOfPins++;
  }
  void AnaRead::readAll()
  {
    for(int i = 0; i < numOfPins; i++)
    {
      data[i] = analogRead(pins[i]);
    }
  }
  int AnaRead::getNumOfPins()
  {
    return numOfPins;
  }
  int* AnaRead::getDataPtr()
  {
    return data;
  }
  AnaRead::AnaRead(int _maxPins)
  {
    int pins[_maxPins];
    int data[_maxPins];
  }
