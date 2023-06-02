#include <Arduino.h>
#include <config.h>
#include <hand_data.h>
#include <PCA9685.h>
#include <IO.h>

#define COUNT_LOW 0
#define COUNT_HIGH 8888
#define TIMER_WIDTH 16 //was 8                                                                                                                                          
#define Hz 50

//if(debug){Serial.println("@: ");}


void setupServo(servoData S){
  if(debug){Serial.print("@setupServo: '");}
  if(debug){Serial.print(S.fName);}
  if(debug){Serial.println("'");}
  
  
}



void declareHandOutputs(){
  if(debug){Serial.println("@declareHandOutputs: ");}
  // for(int i = 1; i <= 6; i++) {
  //   setupServo(handProfile[i-1]);
  // }
  setupPCA9685();
}



// void declareHandOutputs(){
//   ledcSetup(1, Hz, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
//   ledcAttachPin(handProfile[0].serPin, 1);   // GPIO 22 assigned to channel 1

//   ledcSetup(2, Hz, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
//   ledcAttachPin(handProfile[1].serPin, 2);   // GPIO 22 assigned to channel 1

//   ledcSetup(3, Hz, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
//   ledcAttachPin(handProfile[2].serPin, 3);   // GPIO 22 assigned to channel 1

//   ledcSetup(4, Hz, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
//   ledcAttachPin(handProfile[3].serPin, 4);   // GPIO 22 assigned to channel 1
  
//   ledcSetup(5, Hz, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
//   ledcAttachPin(handProfile[4].serPin, 5);   // GPIO 22 assigned to channel 1

//   ledcSetup(6, Hz, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
//   ledcAttachPin(handProfile[5].serPin, 6);   // GPIO 22 assigned to channel 1

// }

// void declareOutputs(){
//   pinMode(handProfile[0].serPin,OUTPUT);
//   pinMode(handProfile[1].serPin,OUTPUT);
//   pinMode(handProfile[2].serPin,OUTPUT);
//   pinMode(handProfile[3].serPin,OUTPUT);
//   pinMode(handProfile[4].serPin,OUTPUT);
//   pinMode(handProfile[5].serPin,OUTPUT);
// }

void moveHand(sPosition fingerPos){
  if(debug){Serial.print("@moveHand: ");}
  writeServo(fingerPos.pinkyF,  handProfile[0]);
  writeServo(fingerPos.ringF,   handProfile[1]);
  writeServo(fingerPos.middleF, handProfile[2]);
  writeServo(fingerPos.indexF,  handProfile[3]);
  writeServo(fingerPos.thumbF,  handProfile[4]);
  writeServo(fingerPos.wrist,   handProfile[5]);
  if(debug){Serial.print("\n\n");}
}