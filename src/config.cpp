#include <Arduino.h>
#include <config.h>

String wireless_mode = "ESPNOW";

int ledBacklight = 7864; // Initial TFT backlight intensity on a scale of 0 to 255. Initial value is 80.
// Setting PWM properties, do not change this!

sPosition currentPos = {0,0,0,0,0,0};

// Chose the mode of the device

byte mode = 5;

// 0 no debug, 1 single pair debug, 2 write all 
byte debug = 2;

//chose the sensor to be debuged (if applicable)

byte debug_sensor = 2;


//chose the servo to be debuged (if applicable)

byte debug_servo = 2;


// How long to wait after moving a servo

byte servoDelayCoeff = 0;

// Comunication speed over serial(usb or legacy bt)

//int baudRate = 9600;
int baudRate = 115200;
