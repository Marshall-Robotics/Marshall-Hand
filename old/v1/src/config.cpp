#include <Arduino.h>
#include <config.h>


// Chose the mode of the device

byte mode = 2;



//chose the sensor to be debuged (if applicable)

byte debug_sensor = 2;


//chose the servo to be debuged (if applicable)

byte debug_servo = 2;


// How long to wait after moving a servo

byte servoDelayCoeff = 0;

// Comunication speed over serial(usb or legacy bt)

int baudRate = 9600;