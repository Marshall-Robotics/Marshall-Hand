// this is the main.cpp file for the Hand Kinesis project, it is just a draft at the moment


#include <Arduino.h>
#include <config.h>
#include <hand_data.h>
#include <display.h>
#include <modes.h>
#include <ezButton.h>
#include <wireless.h>
#include <hand.h>

#define PCA9685_enablePin 16 //enable pin for PCA9685

ezButton Lbutton(L_BUTTON);  // create ezButton object that attaches to L_BUTTON
ezButton Rbutton(R_BUTTON);  // create ezButton object that attaches to R_BUTTON

void UserModeSwitch(){
  Serial.println("\n\n@UserModeSwitch()");
  Serial.println("");
  for (int n = 0; n < 500; n++)
  {
    bool printMSG = (0 == (n % 100)); //print every 100 loops

    if(debug == 2 &&  printMSG) {
      Serial.print("waiting for user input(");
      Serial.print(n/100);
      Serial.print("/5)...     ");
    }
    else vTaskDelay(5);

    vTaskDelay(10);

    Rbutton.loop();
    Lbutton.loop();
    
    if(Rbutton.isPressed()&&mode<6){
        Serial.println("\n\nR Button pressed\n");
        mode++;
       displaySettings();
       n=0;
    }
    if(Lbutton.isPressed()&&mode>1){
      Serial.println("\n\nButton pressed\n");
      mode--;
      displaySettings();
      n=0;
    }
    
  }
}

void SysInit(){
  Serial.println("\n\n@SysInit()");

  pinMode(L_BUTTON, INPUT_PULLUP);
  pinMode(R_BUTTON, INPUT_PULLUP);

  pinMode(relayPin,OUTPUT); //enable output for relay

}

void setup() {
  Serial.begin(baudRate); //start serial
  Serial.println("\n\nStarting setup():");

  SetupDisplay();
  
  displaySettings();

  SysInit();

  declareHandOutputs();

  UserModeSwitch();

  Serial.print("\n\n\nMode: ");
  Serial.println(mode);

  digitalWrite(PCA9685_enablePin, HIGH); //enable PCA9685


  switch (mode)
  {
  case 1:
    serialControl1(); //TODO
    Serial.write("@serialControl())");
    break;
  
  case 2: 
    Serial.println("@readMove())");
    displayMode2();
    delay(3000);
    readMove2();
    break;

  case 3:
    Serial.println("@WebServer())");
    setupWebServer(); //Start WebServer & Connect
    
    displayMode3();
    while(true){
      Serial.println("@WebServer())");
      delay(500);
    }
    break;
  
  case 4:
    Serial.println("@wirelessControl()");
    wirelessSetup();

    wirelessControl4();
    break;
  
  case 5:
    Serial.write("@readPrint()");
    displayMode5();
    delay(3000);
    readPrint5();

    break;

  case 6:
    while(true){
      Serial.write("@UI Test()");
      delay(500);
    }
    break;
  default:
    Serial.write("Looks like the mode is wrong");
    break;
  }

  Serial.println("\n\n\nProgram complete");
}

void loop(){
  ;;
}
