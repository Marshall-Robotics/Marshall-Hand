#include <Arduino.h>
#include <config.h>
#include <hand_data.h>
#include <IO.h>

String byteToStr(byte num){ //verified
    String sOut = String(num);
    while(true){
      if(sOut.length() > 2){
        break;
      }
      sOut = String(0)+sOut;  
    }
    return sOut;
}
String intToStr(int num){ //verified
    String sOut = String(num);
    while(true){
      if(sOut.length() > 3){
        break;
      }
      sOut = String(0)+sOut;  
    }
    
    return sOut;
}


byte readPrintPotVal(potData & pData) { 
    Serial.println("pot: "+String(pData.potPin));
    int potVal = analogRead(pData.potPin); //reads value from pot
    Serial.print("rawIN:"+intToStr(potVal)+" ");
    potVal = map(potVal, pData.minP, pData.maxP, 0, 100); //map pot value
    Serial.print("map:"+byteToStr(potVal)+" ");
    if (potVal <  0) {//constraints values 
      potVal = 0;
    } else if (potVal > 100) {
      potVal = 100;
    }
    Serial.print("const:"+byteToStr(potVal)+" ");

    //shuffles arround averages in memory
    pData.prevReading = pData.potReading;
    pData.potReading = (potVal + pData.prevReading) / 2;
    Serial.print("avrOUT:"+byteToStr(pData.potReading)+" ");
  
  return pData.potReading;
}

/*reads values from potentiomentes, and returns a position value*/
sPosition readPotValPositions() {
  sPosition inputPosition{ //confirmed
    readPotVal(readerProfile[0]),
    readPotVal(readerProfile[1]),
    readPotVal(readerProfile[2]),
    readPotVal(readerProfile[3]),
    readPotVal(readerProfile[4]),
    readPotVal(readerProfile[5])
  };
  return inputPosition;
}

/*reads values from potentiomentes, and returns a position value*/
sPosition readPrintPotValPositions() {
  sPosition inputPosition{
    readPrintPotVal(readerProfile[0]),
    readPrintPotVal(readerProfile[1]),
    readPrintPotVal(readerProfile[2]),
    readPrintPotVal(readerProfile[3]),
    readPrintPotVal(readerProfile[4]),
    readPrintPotVal(readerProfile[5])
  };
  Serial.println();
  return inputPosition;
}

