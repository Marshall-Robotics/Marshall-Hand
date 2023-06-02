// Display.h file
#ifndef display_h_
#define display_h_

#define mode_x 50
#define mode_y 75
#define mode_font 7

#define hand_message_x 25
#define hand_message_y 5

#define hand_message_font 2
#define hand_message_title_font 4
#define hand_message_version_font 2

#define mode_message_x 15
#define mode_message_y 130
#define mode_message_font 2

#define mode_description_message_x 5
#define mode_description_message_y 5
#define mode_description_message_font 2

#define mode_description_mode_x 55
#define mode_description_mode_y 75
#define mode_description_mode_font 7

#define mode_description_mode_text_x 35
#define mode_description_mode_text_y 130
#define mode_description_mode_text_font 4



//#include <WiFi.h>

#include <TFT_eSPI.h>

#include <Arduino.h>
#include <config.h>

#include <hand_data.h>

#include <IO.h>

extern TFT_eSPI tft;
extern TFT_eSprite frame;

void SetupDisplay();

void displaySettings();

void displayMode2();

void displayMode3();

void displayMode5();

void displaySpos(sPosition pos);
#endif