/*------------------------------------------------------------------------------
 * void timeCheck(void)
 * checks the loop time and makes the loop in a constant time interval. 
 *----------------------------------------------------------------------------*/
 
 void timeCheck(void){
//   unsigned long timeSince = timeElapsed(timeStamp);
//   Serial.println(timeSince);
   if(areWeThereYet(timeStamp, controlTime)){
     unsigned long timeSince = timeElapsed(timeStamp);
     if(uartPrint) Serial.print("Late by: ");
     if(uartPrint) Serial.print(timeSince-controlTime);
     if(uartPrint) Serial.println(" us!");
   }
   else{
     do{
     }while(!areWeThereYet(timeStamp, controlTime));                 // kill time till next "void Loop" should execute
//     if(uartPrint) Serial.println(timeElapsed(timeStamp));
   }
 }
 
 /*------------------------------------------------------------------------------
 * void stateTime(struct ALPS *alitemp)
 * time out after 10 hours of chargeing or balancing
 *----------------------------------------------------------------------------*/
 void stateTime(struct ALPS *p){
   unsigned long timeSince= timeElapsed(p->timeKeepingStamp);  // update time in the mode
   p->timeKeepingStamp=micros();
   p->microseconds+=timeSince;   
   if (p->microseconds>ONEMINUTE){
       p->microseconds-=ONEMINUTE;
       p->minutes++;
   }
//   if (p->minutes>60){
//       p->minutes-=60;
//       p->hours++;
//   }
 }
 
 /*------------------------------------------------------------------------------
 * void timeReset(void)
 * reset the mode time, selfCheck, and flag override
 *----------------------------------------------------------------------------*/
 
 void timeReset(struct ALPS *p){
//   p->hours=0;
   p->minutes=0;
   p->microseconds=0;
   p->timeKeepingStamp=micros();
 }
 
 /*------------------------------------------------------------------------------
 * boolean areWeThereYet(const unsigned long &referenceTimeStamp, const long &waitTime)
 * returns true if waitTime has elapsed since referenceTimeStamp
 * returns false if not
 *----------------------------------------------------------------------------*/
 boolean areWeThereYet(const unsigned long &referenceTimeStamp, const long &waitTime){
   unsigned long timeSince= timeElapsed(referenceTimeStamp);
   if (timeSince>=waitTime)
     return true;
   else
     return false;
 }
 
 /*------------------------------------------------------------------------------
 * long timeElapsed(const unsigned long &referenceTimeStamp)
 * returns the time elapsed since referenceTimeStamp
 *----------------------------------------------------------------------------*/
 long timeElapsed(const unsigned long &referenceTimeStamp){
   unsigned long currentTimeStamp =micros();
   long timeSince=0;
   if (referenceTimeStamp > currentTimeStamp){                // check if a rollover has occured
      timeSince= ~(referenceTimeStamp - currentTimeStamp)+1;              // correct for rollover
    }
   else timeSince = currentTimeStamp-referenceTimeStamp;
   return timeSince;
 }
