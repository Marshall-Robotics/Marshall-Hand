#ifndef _IO_H
#define _IO_H
#include "esp32-hal-ledc.h"
#include <PCA9685.h>
#include <Arduino.h>
#include <config.h>

void setupPWM(int pin, int channel, int freq, int resolution);
void setupSoftwarePWM(int pin, int channel, int freq, int resolution);

void writeServo( byte sPos, servoData S);

byte readPotVal(potData &pData);

#endif