#include "SoftwareSerial.h"

SoftwareSerial rx(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rx.begin(9600);
  Serial.println("Reciever booting up");

}

void loop() {
  // put your main code here, to run repeatedly:
  String msg = "";
  //Recieve messages and print them:
  /*
  while(rx.available())
  {
    msg += rx.read();
  }
  if(msg != "")
  {
    Serial.print("Recieved a message: ");
    Serial.println(msg);
  }
  msg = "";
  while(Serial.available())
    msg += Serial.read();
  if(msg != "")
    rx.print(msg);
  
  */
  String input = "";
  char in;
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
      //rx.print('c');
    }
  }
  Serial.println(input);
}
