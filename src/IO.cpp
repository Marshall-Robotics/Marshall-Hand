#include <io.h>


void setupPWM(int pin, int channel, int freq, int resolution){
  if(debug){
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "setupPWM(%d, %d, %d, %d)", pin, channel, freq, resolution);
    Serial.println(buffer);
  }
  pinMode(pin, OUTPUT);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(pin, channel);
  ledcWrite(channel, 0);
}

void setupSoftwarePWM(int pin, int channel, int freq, int resolution){
  if(debug){
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "setupSoftwarePWM(%d, %d, %d, %d)", pin, channel, freq, resolution);
    Serial.println(buffer);
  }
  pinMode(pin, OUTPUT);
  // ledcSetup(channel, freq, resolution);
  // ledcAttachPin(pin, channel);
  // ledcWrite(channel, 0);
}


void writeServo(byte sPos, servoData S){

  int dTime = map(sPos, 0, 100, S.minS, S.maxS );
  
  setServoPulse(S.channel, dTime);

   if(debug == 2){
    char buffer[100]; // print  "CHANNEL.PIN:DUTY   "
    snprintf(buffer, sizeof(buffer), "%d:%d  ", S.channel, dTime);
    Serial.print(buffer);
  }

}

// void writeServo( byte sPos, servoData S){

//   int dTime = map(sPos, 0, 100, 0, 1000 )+1000;
  
//   digitalWrite(S.serPin,HIGH); 
//   delayMicroseconds(dTime); // waits 1000-2000 uS while forming the PWM signal
//   digitalWrite(S.serPin,LOW);

//    if(debug == 2){
//     char buffer[100]; // print  "CHANNEL.PIN:DUTY   "
//     snprintf(buffer, sizeof(buffer), "%d.%d:%d  ", S.channel, S.serPin, dTime);
//     Serial.print(buffer);
//   }

// }

// //Nice & fast 
// void writeServo(byte sPos, servoData S){

//   // Map the servo position from [0, 100] to the servos [duty_min, duty_max].
//   int duty = map(sPos, sPos_MIN, sPos_MAX, S.minS, S.maxS);
//   //int duty = map(sPos, 0, 100, 1638, 7864);

//   // Write the duty to the servo. (CHANNEL, DUTY)
//   ledcWrite(S.channel, duty); 

//   if(debug == 2){
//     char buffer[100]; // print  "CHANNEL:DUTY   "
//     snprintf(buffer, sizeof(buffer), "%d.%d:%d  ", S.channel, S.serPin, duty);
//     Serial.print(buffer);
//   }

// }

byte readPotVal(potData &pData) { //verified
    int potVal = analogRead(pData.potPin); //reads value from pot
    
    potVal = map(potVal, pData.minP, pData.maxP, 0, 100); //map pot value

    if (potVal <  0) {//constraints values 
      potVal = 0; 
    } else if (potVal > 100) {
      potVal = 100;
    }
    
    //shuffles arround averages in memory
    pData.prevReading = pData.potReading;
    pData.potReading = (potVal + pData.prevReading) / 2;
  
  return pData.potReading;
}
