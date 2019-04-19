#include "WheelLight.h"

WheelLight::WheelLight(Transmitter *incoming)
{
    RGBStateInHere = incoming;
}

bool WheelLight::run()
{
    Serial.println("LightUpdate: " + RGBStateInHere->RGBState());
    return true;
}