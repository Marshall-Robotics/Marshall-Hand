#include <Arduino.h>
#include <config.h>
#include <data.h>

void writeServo( byte sPos, servoData S){
  int dTime = map(sPos, 0, 100, S.minS, S.maxS )+1000;

  digitalWrite(S.serPin,HIGH); 
  delayMicroseconds(dTime); // waits 1000-2000 uS while forming the PWM signal
  digitalWrite(S.serPin,LOW);
}

void writePrintServo( byte sPos, servoData S){
  Serial.print("S:" + String(sPos) + " ");

  int dTime = map(sPos, 0, 100, S.minS, S.maxS )+1000;
  
  Serial.print("dT:" + String(dTime) + ", "+ String(S.serPin) + " ");

  digitalWrite(S.serPin,HIGH); 
  delayMicroseconds(dTime); // waits 1000-2000 uS while forming the PWM signal
  digitalWrite(S.serPin,LOW);
}

void moveHand(sPosition fingerPos){
writeServo(fingerPos.pinkyF,  handProfile[0]);
writeServo(fingerPos.ringF,   handProfile[1]);
writeServo(fingerPos.middleF, handProfile[2]);
writeServo(fingerPos.indexF,  handProfile[3]);
writeServo(fingerPos.thumbF,  handProfile[4]);
writeServo(fingerPos.wrist,   handProfile[5]);
}

void movePrintHand(sPosition fingerPos){
writePrintServo(fingerPos.pinkyF,  handProfile[0]);
writePrintServo(fingerPos.ringF,   handProfile[1]);
writePrintServo(fingerPos.middleF, handProfile[2]);
writePrintServo(fingerPos.indexF,  handProfile[3]);
writePrintServo(fingerPos.thumbF,  handProfile[4]);
writePrintServo(fingerPos.wrist,   handProfile[5]);
Serial.println();
}