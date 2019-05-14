
#include "SoftwareSerial.h"
SoftwareSerial rx(2,3);


void setup() {
  // put your setup code here, to run once:
  rx.begin(9600);
  Serial.begin(9600);
  Serial.println("Reciever booting up!");
}

void loop() {
  // put your main code here, to run repeatedly:
  String data = "";
  bool done = false;
  char in;
  String input = "";

  while(input == "")
  {
    if(rx.available())
     in = rx.read();
    if(in == '#')
    {
      while(in != '!')
      {
        if(rx.available())
        {
          in = rx.read();
          input += in;
        }
      }
      //We've recieved a message, send back that we are connected
      rx.print('c');
    }
  }
  Serial.println(input);
  /*
  String tmp = "";
  done = false;
  while(!done)
  {
    tmp += input[0];
    Serial.print("Input before removing: ");
    Serial.printinput);
    input.remove(0);
    if(input[0] == ':')
      done = true;
  }
  
  int numOfReadings = tmp.toInt();

  int output[numOfReadings];
  
  for(int i = 0; i < numOfReadings; i++)
  {    Serial.print('b');

    tmp = "";
    while(input[0] != ',')
    {
      tmp += input[0];
      input.remove(0);
          Serial.print('c');

    }
    data[i] = tmp.toInt();
  }
  Serial.println(data);
*/
}
