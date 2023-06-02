#include <Arduino.h>
#include <config.h>
#include <hand_data.h>

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
    
void childMode(){

  // sPosition currentPos = readPotValPositions();
  // while(isObsene(currentPos)){
  //   currentPos = readPotValPositions();
  //   moveHand(PEACE);
  // }
}