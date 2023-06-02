
#include <Arduino.h>
#include <config.h>
#include <hand_data.h>
#include <hand.h>
#include <display.h>
#include <sensor.h>
#include <wireless.h>
#include <obsenity_filter.h>

void serialControl1(){
  while (true)
  {
    /* code */
  }
  
} 

void readMove2(){
  
  byte count = 0;
  while (true)
  {
    count++;
    
    sPosition currentPos = readPotValPositions();

    // if(true){
    //   if(isObsene(currentPos)){
    //     childMode();
    //   }
    // }
    displaySpos(currentPos);
    moveHand(currentPos);

    // ledBacklight = 2*currentPos.wrist;
    // ledcWrite(LCD_pwm_LedChannel_TFT, ledBacklight);
    
    // Enables power to the servos. 
    if(currentPos.wrist>20){
      digitalWrite(relayPin,HIGH);
    }else{
      digitalWrite(relayPin,LOW);
    }

  }
  
} 

void wirelessControl4(){
  //sPosition currentPos = {0,0,0,0,0,0};
  byte count =0;
  while (true)
  {
    count++;
    if (wireless_mode == "ESPNOW") {
      // read from espnow
      Serial.println("ESPNOW");
      vTaskDelay(1000);

    } else if (wireless_mode == "WiFi") {
      // read from wifi
      //currentPos = read_WiFi_ValPositions();

    } else if(wireless_mode == "BT"){
      // read from bluetooth
      //currentPos = read_BT_ValPositions();

    }else{
      Serial.println("Error: wireless mode not defined");
    }
    
    //to print the hex values
    //sPositionToHex(currentPos);


    // if(true){
    //   if(isObsene(currentPos)){
    //     childMode();
    //   }
    // }
    //displaySpos(currentPos);
    //moveHand(currentPos);

    // ledBacklight = 2*currentPos.wrist;
    // ledcWrite(LCD_pwm_LedChannel_TFT, ledBacklight);
    // Enables power to the servos. 
    if(currentPos.wrist>20){
      digitalWrite(relayPin,HIGH);
    }else{
      digitalWrite(relayPin,LOW);
    }
  }
  
} 

void readPrint5(){
  while (true)
  {
    displaySpos(readPotValPositions());
  }
  
} 


  

