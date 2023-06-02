//config.h
#include <Arduino.h>
/** This file contains the declarations for the global variables used
 *  in the rest of the program as changeable settings.
**/
#ifndef config
#define config
#include <hand_data.h>

#define hand_Firmware_version "v2.0"




#define TFT_BL   4            // LED back-light control pin

#define L_BUTTON 35
#define R_BUTTON 0

#define LCD_pwm_Freq 5000
#define LCD_pwm_Resolution 8
#define LCD_pwm_LedChannel_TFT 0

#define startUp_delay 200

#define sPos_MAX 100
#define sPos_MIN 0

#define relayPin 2

extern String wireless_mode;

extern sPosition currentPos;


extern int ledBacklight;

/*
    Mode 1: serial control
    Mode 2: read sensor and move (deploy mode)
    Mode 3: debug mode read & move
    Mode 4: bluetooth control
    Mode 5: read and print
*/ 
extern byte mode;

extern byte debug;
//0-5 sensorProfile Number
extern byte debug_sensor;

//0-5 handProfile Number
extern byte debug_servo;

// time in ms
extern int cycleDelay; 

/** Coefficient of the time delay
 *  in microseconds that will be 
 *  waited for the servo to move.
 *  0 = no delay. (0-512)
 */
extern byte servoDelayCoeff;

/**For communicating with the computer, use one of these rates:
 * 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 
 * 38400, 57600, or 115200.
 */
extern int baudRate;


#endif