#include "DataReceiver.h"

DataReceiver::DataReceiver(uint8_t _led_pin, CRGB* _leds, uint32_t _now) : led_pin(_led_pin), leds(_leds)
{
  pinMode(led_pin, OUTPUT);
}

bool DataReceiver::canRun(uint32_t now)
{
  if (Serial.available()) //This task should run if there is data to recieve
    return true;
  else
    return false;
}

void DataReceiver::run(uint32_t now)  //will be run by the scheduler when canRun (right above) returns true
{
  char in;            //variables to hold input from Serial
  String input = "";

  in = Serial.read(); //Read a byte
  if (in == '#')  //If the read byte is a '#' we are at the start of a message. 
  {
    while (in != '!') // Keep reeding, until an '!' is received:
    {
      if (Serial.available())
      {
        in = Serial.read();
        input += in;
      }
    }
    if (input[0] == '1') //Change LED command
    {
      int i = 2;
      int j = 0;
      int led_data[4];
      String data = "";

      while (input[i] != '!') //Loop through the message, and store the recieved int's in the led_data array
      {
        if (input[i] != ',')
          data += input[i];
        else
        {
          led_data[j] = data.toInt();
          data = "";
          j++;
        }
        i++;
      }

      leds[led_data[0]].setRGB(led_data[1], led_data[2], led_data[3]);  //and set the LED
      FastLED.show(); //updating the LED strip

    }
    else if (input[0] == '2') //Resistor LED command
    {
      String data = "";
      int i = 2;
      while (input[i] != ',')//read the int:
      {
        data += input[i];
        i++;
      }
      analogWrite(led_pin, 255 - data.toInt()); //and update the LED
    }
  }
}
