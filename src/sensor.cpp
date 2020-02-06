#include <Arduino.h>
#include <config.h>
#include <data.h>

String byteToStr(byte num){
    String sOut = String(num);
    if(sOut.length() < 3){
        sOut = String(0)+sOut;
    }
    return sOut;
}
String intToStr(int num){
    String sOut = String(num);
    if(sOut.length() < 3){
        sOut = String(0)+sOut;
    }
    return sOut;
}

byte readPotVal(potData &pData) {
    int potVal = analogRead(pData.potPin); //reads value from pot
    
    potVal = map(potVal, pData.minP, pData.maxP, 0, 100); //map pot value

    if (potVal <  0) {//constraints values 
      potVal = 0;
    } else if (potVal > 100) {
      potVal = 100;
    }
    
    //shuffles arround averages in memory
    pData.prevReading = pData.potReading;
    pData.potReading = (potVal + pData.prevReading) / 2;
  
  return pData.potReading;
}

byte readPrintPotVal(potData &pData) {
    Serial.println("pot: "+byteToStr(pData.potPin));
    int potVal = analogRead(pData.potPin); //reads value from pot
    Serial.print("rawIN:"+byteToStr(potVal)+" ");
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
    Serial.print("avrOUT:"+intToStr(pData.potReading)+" ");
  
  return pData.potReading;
}

/*reads values from potentiomentes, and returns a position value*/
sPosition readPotValPositions() {
  sPosition inputPosition{
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

