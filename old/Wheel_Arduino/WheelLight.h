#ifndef WHEELIGHT_H
#define WHEELIGHT_H

#include "Task.h"
#include "Arduino.h"
#include "Talker.h"

class WheelLight : public Task
{
private:
    Transmitter * RGBStateInHere;
public:
    WheelLight(Transmitter *incoming);
    virtual bool run();
};

#endif