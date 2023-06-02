#include <Arduino.h>
#include <hand_data.h>
/** This file contains the declarations for the global variables used
 *  in the rest of the program as flags and data. It also contains the 
 *  custom data structures and preset defaults. 
**/
#ifndef hand
#define hand

void writeServo( byte sPos, servoData S);

void declareHandOutputs();

void moveHand(sPosition fingerPos);

#endif