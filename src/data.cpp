#include <Arduino.h>
#include <data.h>

potData readerProfile[6] {
  {0, 0, 900, 50, 50},
  {1, 0, 900, 50, 50},
  {2, 0, 900, 50, 50},
  {4, 0, 900, 50, 50},
  {5, 0, 900, 50, 50},
  {3, 0, 900, 50, 50}
};

servoData handProfile[6] {
  {"Pinky",         3,  100, 900},
  {"ring Finger",   5,  100, 900},
  {"middle Finger", 6,  100, 900},
  {"index",         9,  100, 900},
  {"thumb",         10, 100, 900},
  {"DISABLED",      11, 100, 900}
};

sPosition NUMBERONE {0, 0,  0, 90, 90};
sPosition PEACE     {0, 0, 90, 90, 90};