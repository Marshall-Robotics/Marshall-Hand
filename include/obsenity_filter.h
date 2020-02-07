#include <Arduino.h>
#include <data.h>
/** This file contains the declarations for the global variables used
 *  in the rest of the program as flags and data. It also contains the 
 *  custom data structures and preset defaults. 
**/
#ifndef obsenity_filter
#define obsenity_filter

extern bool isObsene(sPosition pos);

void transition(sPosition init, sPosition final);

#endif