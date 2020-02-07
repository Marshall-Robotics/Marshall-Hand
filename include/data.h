#include <Arduino.h>
/** This file contains the declarations for the global variables used
 *  in the rest of the program as flags and data. It also contains the 
 *  custom data structures and preset defaults. 
**/
#ifndef data
#define data

// finger Pin min max
struct servoData {
  String fName;
  byte serPin;
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

// calibration data for hand.

extern servoData handProfile[6];

// calibration and state data for sensor.

extern potData readerProfile[6];

extern sPosition NUMBERONE;

extern sPosition PEACE;

#endif