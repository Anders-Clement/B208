#ifndef AREAD_H
#define AREAD_H

class AnaRead{
public:
  void addReadPin(int pin);
  void readAll();
  int getNumOfPins();
  int* getDataPtr();
  AnaRead(int maxPins);
private:
  int numOfPins;
  int pins[];
  int data[];
};

#endif
