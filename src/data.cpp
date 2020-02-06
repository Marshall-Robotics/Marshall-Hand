#include <Arduino.h>
#include <data.h>

potData readerProfile[6] {
  {0, 0, 1023, 50, 50}, //g "pinky"
  {1, 0, 1023, 50, 50},  //g "ring finger"
  {2, 0, 1023, 50, 50},  //g "middle finger"
  {5, 0, 1023, 50, 50},  //g "index"
  {3, 0, 1023, 50, 50},
  {4, 0, 1023, 50, 50}
};

servoData handProfile[6] {
  {"Pinky",         3,  100, 1000},
  {"ring Finger",   5,  100, 1000},
  {"middle Finger", 6,  -100, 900},
  {"index",         10,100, 900},
  {"thumb",         11,  0, 1100},
  {"DISABLED",      9, 100, 900}
};

sPosition NUMBERONE {0, 0,  0, 90, 90};
sPosition PEACE     {0, 0, 90, 90, 90};