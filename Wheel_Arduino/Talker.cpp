#include "Arduino.h"
#include "Talker.h"
#include "IMUAngle.h"

Transmitter::Transmitter(IMUAngle *angleClass)
{
    driver = new RH_ASK(2000, 12, 11, 0);
    manager = new RHReliableDatagram(*driver, SERVER_ADDRESS);
    linkToAngler = angleClass;
    if (!(manager->init()))
    {
        Serial.println("Transmitter Server Failed to initilize");
    }
}

bool Transmitter::run()
{
    data[0] = (uint8_t)linkToAngler->CurrentAngle;
    if (manager->available())
    {
        // Wait for a message addressed to us from the client
        uint8_t len = sizeof(buf);
        uint8_t from;
        if (manager->recvfromAck(buf, &len, &from))
        {
        Serial.print("got request from : 0x");
        Serial.print(from, HEX);
        Serial.print(": ");
        Serial.println((char*)buf);

        // Send a reply back to the originator client
        if (!manager->sendtoWait(data, sizeof(data), from))
            Serial.println("sendtoWait failed");
        }
    }
    return true;
}

int Transmitter::RGBState()
{
    return RGBStatus;
}