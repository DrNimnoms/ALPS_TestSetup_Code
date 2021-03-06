/*------------------------------------------------------------------------------
 * void checkMode()
 * checks APLS systems mode
 *----------------------------------------------------------------------------*/
  void checkMode(){
    if(alps[0].mode==RUN || alps[1].mode==RUN){
      if(alps[0].state==PUMPING || alps[1].state==PUMPING || alps[0].state==INITALIZING || alps[1].state==INITALIZING) digitalWrite(POWERpin,HIGH);
      else digitalWrite(POWERpin,LOW);
    }
    else digitalWrite(POWERpin,LOW);
    
    for(int i=0;i<ALPSnum;i++){
      
      if(!alps[i].supplyOn){
         if (alps[i].reactorPres >= maxPres + 5){
           alps[i].countH2=true;
           digitalWrite(alps[i].reactorVPin,HIGH);      // turn reactor valve on   
         }
         else if(alps[i].reactorPres <= maxPres - 5){
           alps[i].countH2=false;
           digitalWrite(alps[i].reactorVPin,LOW);
         }
      }
      
      if(alps[i].totalH2 >= alps[i].h2expected) stopMode(&alps[i]);
      if(alps[i].mode==RUN) checkState(&alps[i]);
    }
  }

/*------------------------------------------------------------------------------
 * void reset(struct ALPS *p)
 * resets the APLS system
 *----------------------------------------------------------------------------*/
 void reset(struct ALPS *p){
   p->cycle=0;
   p->waterNeeded=waterNeededMin;
   p->totalWater=0;
   p->totalH2=0;
   p->waterInjected=0;
   p->state=INITALIZING;
 }
 
/*------------------------------------------------------------------------------
 * void startMode(struct ALPS *p)
 * starts the APLS system reactor
 *----------------------------------------------------------------------------*/
 void runMode(struct ALPS *p){
   timeReset(p);
   p->mode=RUN;
 }
 
/*------------------------------------------------------------------------------
 * void stopMode(struct ALPS *p)
 * starts the APLS system reactor
 *----------------------------------------------------------------------------*/
 void stopMode(struct ALPS *p){
   stopActuators(p);
   p->mode=STOP;
 }
 

