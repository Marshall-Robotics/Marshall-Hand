#include <Arduino.h>
#include <config.h>
#include <data.h>
#include <hand.h>
#include <sensor.h>
#include <obsenity_filter.h>


void childMode(){
  sPosition currentPos = readPotValPositions();
  transition(currentPos,PEACE);
  while(isObsene(currentPos)){
    currentPos = readPotValPositions();
    moveHand(PEACE);
  }
  transition(PEACE, currentPos);
}
  

void serialControl1(){
  while (true)
  {
    /* code */
  }
  
} 

void readMove2(){
  byte count =0;
  while (true)
  {
    count++;
    
    sPosition currentPos = readPotValPositions();

    if(true){
      if(isObsene(currentPos)){
        childMode();
      }
    }

    moveHand(currentPos);
  }
  
} 

void readMoveDebug3(){
  while (true)
  {
  sPosition currentPos = readPotValPositions();
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