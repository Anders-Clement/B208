#ifndef IMUANGLE_H
#define IMUANGLE_H

#include<Wire.h>
#include "Task.h"

class IMUAngle : public Task
{
private:
    const int MPU=0x68; 
public:
    int16_t CurrentAngle = 0;
    IMUAngle();
    ~IMUAngle();
    virtual bool run();
};


#endif
