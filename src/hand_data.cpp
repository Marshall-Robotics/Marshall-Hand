#include <Arduino.h>
#include <hand_data.h>

// (potPin, min, max, potReading, prevReading)
potData readerProfile[6] {
  {25, 0, 4095, 50, 50},  //g "pinky"
  {26, 0, 4095, 50, 50},  //g "ring finger"
  {27, 0, 4095, 50, 50},  //g "middle finger"
  {39, 0, 4095, 50, 50},  //g "index"
  {32, 0, 4095, 50, 50},   //g "Thumb"
  {33, 0, 4095, 50, 50}
};

// // (fName,     channel, pin, minS, maxS)
// servoData handProfile[6] {
//   {"Pinky",         1, 38,  1000,  2000},
//   {"ring Finger",   2, 37,  1000,  2000},
//   {"middle Finger", 3, 15,  1000,  2000},
//   {"index",         4, 12,  1000,  2000},
//   {"thumb",         5, 13,  1000,  2000},
//   {"wrist",         6, 36,  1000,  2000}
// };

// (fName,     channel, pin, minS, maxS)
servoData handProfile[6] {
  {"Pinky",         0, 180,  500},
  {"ring Finger",   1, 180,  500},
  {"middle Finger", 2, 180,  500},
  {"index",         3, 180,  500},
  {"thumb",         4, 100,  400},
  {"wrist",         5, 100,  450}
};


sPosition NUMBERONE {100, 100,  100, 100, 100};
sPosition PEACE     {100, 100, 0, 0, 100};