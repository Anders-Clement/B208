
#include "SoftwareSerial.h" //Softwareserial for wireless module
#include "aRead.h"


SoftwareSerial tx(2,3);

int analogPins[] = {A1, A2, A3, A4, A5};
int digitalPins[] = {7, 8};
String data = "";
long lastTime;
long msgNum = 0;
int ON_LED = 5;
int CONNECTED_LED = 6;

void setup() {
  tx.begin(9600);
  Serial.begin(9600);
  Serial.println("Transmitter booting up...");
  delay(2000);

  for(int i = 0; i < sizeof(analogPins)/sizeof(analogPins[0]); i++)
  {
    pinMode(analogPins[i], INPUT);
  }
  for(int i = 0; i < sizeof(digitalPins)/sizeof(digitalPins[0]); i++)
  {
    pinMode(digitalPins[i], INPUT_PULLUP);
  }

  analogWrite(ON_LED, 2);
}

void loop() {

  //Get currernt time:
  long now = millis();
  if(now > lastTime + 250) //send messages every 50ms, that is, 20 times a second
  {
    msgNum++;
    lastTime = now;
    data += "#"; //Start of message
    int numOfAReadings = sizeof(analogPins)/sizeof(analogPins[0]);
    int numOfDReadings =  sizeof(digitalPins)/sizeof(digitalPins[0]);
    data += numOfAReadings + numOfDReadings;
    data += ":";
    for(int i = 0; i < numOfAReadings; i++)
    {
      data += String(analogRead(analogPins[i]));
      data += ",";
    }
    for(int i = 0; i < numOfDReadings; i++)
    {
      data += digitalRead(digitalPins[i]);
      data += ",";
    }
    data += msgNum;
    data += "!"; //End of message indicator

    //Send data to serial for debugging, and transmit over tx:
    //Serial.println(data);
    tx.print(data);
    //Empty data string:
    data = "";
      
    //Finally check if connected to someone (expect a 'c' from reciever:
    char in = 'a';
    if(tx.available())
    {
      in = tx.read();      
      //flush rx buffer, necessary if a 'c' is recieved more often than messages are sent
      while(tx.available())
      {
        in = tx.read();
      }
    } 
    if(in == 'c')
      analogWrite(CONNECTED_LED, 100);
    else
      analogWrite(CONNECTED_LED, 0);
  } //end of now > lasttime + time_offset
} //End of loop
