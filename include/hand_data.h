#include <Arduino.h>
/** This file contains the declarations for the global variables used
 *  in the rest of the program as flags and data. It also contains the 
 *  custom data structures and preset defaults. 
**/
#ifndef _DATA_H_
#define _DATA_H_

// finger Pin min max
struct servoData {
  String fName;
  byte channel;
  int minS;
  int maxS;
};

// pin min max reading prevReading
struct potData {
  byte potPin;
  int minP;
  int maxP;
  byte potReading;
  byte prevReading;
};

/*Custom data structure, used to store a particular position for
  the hand.
  uses PERCENTAGES not Angles to define positions*/
struct sPosition {
  byte pinkyF;
  byte ringF;
  byte middleF;
  byte indexF;
  byte thumbF;
  byte wrist;
};

// calibration and state data for sensor.

extern potData readerProfile[6];

// calibration data for hand.

extern servoData handProfile[6];

extern sPosition NUMBERONE;

extern sPosition PEACE;

#endif