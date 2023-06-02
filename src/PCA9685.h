//PCA9685.h
#ifndef PCA9685_H_
#define PCA9685_H_


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

void setupPCA9685();
void setServoPulse(byte   n, int pulse);

#endif /* PCA9685_H_ */
