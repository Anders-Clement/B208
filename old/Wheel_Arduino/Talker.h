#ifndef TALKER_H
#define TALKER_H

#include "Arduino.h"
#include "Task.h"

#include <RHReliableDatagram.h>
#include "RH_ASK.h"
#include "SPI.h"
#include "IMUAngle.h" 

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

class Transmitter : public Task
{
    RH_ASK *driver; // Reciver on pin 12, transmitter on pin 11.
    RHReliableDatagram *manager; // Class to manage message delivery and receipt, using the driver declared above

    uint8_t data[4] = {'A','B','C','D'}; // Dont put this on the stack:
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; //RH_ASK_MAX_MESSAGE_LEN is defined in the RHReliableDatagram file.

    int RGBStatus = 0;
    IMUAngle *linkToAngler;

public:
    Transmitter(IMUAngle *angleClass);
    virtual bool run();
    int RGBState();
};

#endif



