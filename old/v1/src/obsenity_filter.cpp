#include <Arduino.h>
#include <config.h>
#include <data.h>

bool isObsene(sPosition pos){
    if(
        pos.pinkyF>50    &&
        pos.ringF >50    &&
        pos.middleF < 50 &&
        pos.indexF>50    ){
            return true;
        }
    return false; 

}
    