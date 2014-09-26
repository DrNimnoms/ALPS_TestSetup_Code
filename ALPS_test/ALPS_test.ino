/*
 created 9/3/2014
 modified 9/5/2014
 by Nima Ghods
 
 ALPS code made to communicate with the Raspbarry Pi
 Circuit: ALPS V1_0 attached to arduino mega
 
 */

//included libraries:
 #include <Arduino.h>
 #include "ALPS.h"           //all ALPS system variables

void setup() {
  Inital();
  Serial.println("\t\t  ALPS system test\n");
}

void loop() {
  timeStamp=micros();                // microseconds since board initialized, overflow/rollover after ~11.9 hours (2^32-1 uS)
                                       // returned in 1 microsecond resolution  
  measNcal();            // meassures and calculats data
  
  checkMode();           // checks Mode
  
  sendData();            //send data
  
  timeCheck();           //tries to keep loop time roughly constant
}
