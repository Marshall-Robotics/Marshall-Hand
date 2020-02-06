#include <Arduino.h>
#include <config.h>
#include <data.h>
#include <hand.h>
#include <sensor.h>


void serialControl1(){
  while (true)
  {
    /* code */
  }
  
} 

void readMove2(){
  while (true)
  {
  sPosition currentPos = readPotValPositions();
  moveHand(currentPos);
  }
  
} 

void readMoveDebug3(){
  while (true)
  {
  sPosition currentPos = readPrintPotValPositions();
  movePrintHand(currentPos);
  }
  
} 

void bluetoothControl4(){
  while (true)
  {
    /* code */
  }
  
} 

void readPrint5(){
  while (true)
  {
    readPrintPotVal(readerProfile[debug_sensor]);
  }
  
} 

void setup() {
  if(mode==1||mode==3||mode==5){ //if mode needs usb serial
    Serial.begin(baudRate); //start serial
  }

  if(mode==4){ // if mode is bluetooth
    //enable bluethooth
  }

  switch (mode)
  {
  case 1:
    serialControl1();
    break;
  
  case 2:
    readMove2();
    break;

  case 3:
    readMoveDebug3();
    break;
  
  case 4:
    bluetoothControl4();
    break;
  
  case 5:
    readPrint5();
    break;
  default:
    if(!Serial){ //if serial not started
    Serial.begin(baudRate); //start serial
    }
    while (true)
    {
      delay(400);
      Serial.write("Looks like the mode is wrong");
    }
    break;
  }
}