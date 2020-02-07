#include <Arduino.h>
#include <config.h>
#include <data.h>
#include <hand.h>

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

void transition(sPosition init, sPosition final){
    sPosition curPosition = init;
    for (byte i = 0; i < 10; i++)
    {   delay(100);
        curPosition = {
            (3/5)*(curPosition.pinkyF)+(2/5)*final.pinkyF,
            (3/5)*(curPosition.ringF)+(2/5)*final.ringF,
            (3/5)*(curPosition.middleF)+(2/5)*final.middleF,
            (3/5)*(curPosition.indexF)+(2/5)*final.indexF,
            (3/5)*(curPosition.thumbF)+(2/5)*final.thumbF,
            };
        moveHand(curPosition);
    }
    
    moveHand(final);
}
    