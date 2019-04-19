#include "IMUAngle.h"
#include "Arduino.h"

IMUAngle::IMUAngle()
{
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B); 
    Wire.write(0);    
    Wire.endTransmission(true);
}

IMUAngle::~IMUAngle()
{
}

bool IMUAngle::run()
{
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);  
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,12,true);

    CurrentAngle=Wire.read()<<8|Wire.read();

    return true;
}