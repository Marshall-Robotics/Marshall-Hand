#include <display.h>


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite frame = TFT_eSprite(&tft);

void drawHandMessage(){
  tft.init();
  tft.setRotation(2);
  frame.createSprite(135, 240);
  frame.drawString("Kinesis", hand_message_x,     hand_message_y,     hand_message_title_font);
  frame.drawString("Kinesis", hand_message_x,     hand_message_y+10,     hand_message_title_font);
  frame.drawString("Hand",    hand_message_x+10,  hand_message_y+35,  hand_message_title_font);
  frame.drawString(hand_Firmware_version, hand_message_x+25,  hand_message_y+55, hand_message_version_font);

  //frame.drawString(WiFi.localIP().toString(), 20, 200, 1);
}

void drawFGmessage(){
  frame.drawString("Designed in Minnesota", 5, 215, 1);
  frame.drawString("By Felipe Galindo", 15, 225, 1);
}


void SetupDisplay(){
  Serial.print("@SetupDisplay()   ");

  setupPWM(TFT_BL, LCD_pwm_LedChannel_TFT, LCD_pwm_Freq, LCD_pwm_Resolution);
  ledcWrite(LCD_pwm_LedChannel_TFT, 2*ledBacklight);

  drawHandMessage();
  drawFGmessage();

  frame.pushSprite(0, 0);

  Serial.println("Display Init: DONE");
}

void displaySettings(){
  frame.drawString(String(mode), mode_x, mode_y, mode_font);

  // if(debug==2){
  //   frame.drawString("dSN:      dSV:", 5, 130, 2);
  //   frame.drawString(String(debug_sensor), 40, 130, 2);
  //   frame.drawString(String(debug_servo), 100, 130, 2);
  // }else if(debug==1){
  //   frame.drawString("Full Debug", 35, 130, 2);
  // }else{
  //   frame.drawString("Debug = FALSE", 30, 130, 2);
  // }

  switch (mode)
  {
    case 1:
      frame.drawString("    SerialCtrl   ", mode_message_x, mode_message_y, mode_message_font);
      break;
    case 2:
      frame.drawString("    readMove     ", mode_message_x, mode_message_y, mode_message_font);
      break;
    case 3:
      frame.drawString("    WebServer    ", mode_message_x, mode_message_y, mode_message_font);
      break;
    case 4:
      frame.drawString(" WirelessControl ", mode_message_x, mode_message_y, mode_message_font);
      break;
    case 5:
      frame.drawString("    readPrint    ", mode_message_x, mode_message_y, mode_message_font);
      break;
    case 6:
      frame.drawString("      UITest     ", mode_message_x, mode_message_y, mode_message_font);
      break;
  }

  frame.pushSprite(0,0);
}


void displayMode2(){
  frame.fillScreen(TFT_BLACK);

  frame.drawString("Moves Hand & prints ", mode_description_message_x, mode_description_message_y, mode_description_message_font);
  frame.drawString("to the screen and ", mode_description_message_x, mode_description_message_y+20, mode_description_message_font);
  frame.drawString("serial interface ", mode_description_message_x, mode_description_message_y+40, mode_description_message_font);
  
  frame.drawString(String(mode), mode_description_mode_x, mode_description_mode_y, mode_description_mode_font);
  frame.drawString("Mode", mode_description_mode_text_x, mode_description_mode_text_y, mode_description_mode_text_font);
  frame.pushSprite(0,0);
}

void displayMode3(){
  frame.fillScreen(TFT_BLACK);

  frame.drawString("Creates WebServer", 10, 5, 2);
  frame.drawString("To enable OTA &", 15, 25, 2);
  frame.drawString("WebSite Control", 20, 45, 2);
  
  frame.drawString(String(mode), 55, 75, 7);
  frame.drawString("Mode", 35, 130, 4);
  //frame.drawString(WiFi.localIP().toString(), 20, 215, 2);
  frame.pushSprite(0,0);
}

void displayMode5(){
  frame.fillScreen(TFT_BLACK);

  frame.drawString("Reads & Prints vals", 5, 5, 2);
  frame.drawString("to the screen and ", 5, 25, 2);
  frame.drawString("serial interface ", 5, 45, 2);
  
  frame.drawString(String(mode), 55, 75, 7);
  frame.drawString("Mode", 35, 130, 4);
  frame.pushSprite(0,0);
}

void displaySpos(sPosition pos){
  frame.fillScreen(TFT_BLACK);
  frame.setTextColor(TFT_WHITE);

  frame.drawString(String(pos.wrist), 5, 5, 2);

  if(pos.wrist>20){
    frame.setTextColor(TFT_BLUE);
  }else{
    frame.setTextColor(TFT_RED);
  }

  frame.drawString(String(pos.pinkyF), 40, 0, 7);
  frame.drawString(String(pos.ringF), 40, 47, 7);
  frame.drawString(String(pos.middleF), 40, 94, 7);
  frame.drawString(String(pos.indexF), 40, 141, 7);
  frame.drawString(String(pos.thumbF), 40, 188, 7);

  frame.pushSprite(0,0);
}