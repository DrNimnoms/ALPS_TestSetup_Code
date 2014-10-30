/*------------------------------------------------------------------------------
 * void reset(struct ALPS *p)
 * resets the APLS system
 *----------------------------------------------------------------------------*/
  void checkState(struct ALPS *p){
    
    switch (p->state) {
      case INITALIZING:
        initialize(p);
        break;
      case SUPPLYING:
        supply(p);
        break;
      case WAIT1:
        wait1(p);
        break;
      case INJECTING:
        inject(p);
        break;
      case WAIT2:
        wait2(p);
        break;
      case PUMPING:
        pump(p);
        break;
      case REACTING:
        reacting(p);
        break;
      default: 
        break;
    }
  }
 
 /*------------------------------------------------------------------------------
 * void initialize(struct ALPS *p)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void initialize(struct ALPS *p){
   digitalWrite(POWERpin,HIGH);
   digitalWrite(p->waterVPin,HIGH);      // turn water valve on
   float pumpW= p->totalWater - p->waterInjected;
   int wNeedTempo=p->waterNeeded;
   if(p->manualWater) wNeedTempo=p->manWaterpumped;
   
   if ( pumpW >= wNeedTempo || p->waterPres >= 750){
//     p->pumpOn=false;
     digitalWrite(p->pumpPin,LOW);
     p->pumpCount++;
   }
   else {
     digitalWrite(p->pumpPin,HIGH);      // turn pump on
     p->pumpCount = 0;
   }
   
   if(p->pumpCount>15){
     stopActuators(p);
     p->state=SUPPLYING;
   }
 }
 
  /*------------------------------------------------------------------------------
 * void supply(struct ALPS *p)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void supply(struct ALPS *p){

   p->countH2=true;
   p->supplyOn=true;
   digitalWrite(p->reactorVPin,HIGH);      // turn reactor valve on   
   
   if ( p->reactorPres <= minPres){
     stopActuators(p);
     p->countH2=false;
     p->state=WAIT1;
     p->cycle++;
     p->waterNeeded += waterNeededRate;
     p->waterNeeded=min(p->waterNeeded,waterNeededMax);
     timeReset(p);
   }
 }
 
  /*------------------------------------------------------------------------------
 * void wait1(struct ALPS *p)
 * wait time between supply and injection
 *----------------------------------------------------------------------------*/
 void wait1(struct ALPS *p){
   if ( p->minutes >= wait1Time){
     p->state=INJECTING;
   }
 }
 
  /*------------------------------------------------------------------------------
 * void inject(struct ALPS *p)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void inject(struct ALPS *p){

   digitalWrite(p->injectorVPin,HIGH);      // turn water injection valve on
   
   if ( p->reactorPres >= p->waterPres){
     stopActuators(p);
     p->state=WAIT2;
     p->waterInjected=p->totalWater;
     timeReset(p);
   }
 }
 
  /*------------------------------------------------------------------------------
 * void wait2(struct ALPS *p)
 * wait time between injection and pump
 *----------------------------------------------------------------------------*/
 void wait2(struct ALPS *p){
   if ( p->minutes >= wait2Time){
     p->state=PUMPING;
   }
 }
 
 /*------------------------------------------------------------------------------
 * void pump(struct ALPS *p)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void pump(struct ALPS *p){
   
//   p->pumpOn=true;
   digitalWrite(POWERpin,HIGH);
   digitalWrite(p->waterVPin,HIGH);      // turn water valve on
   float pumpW=p->totalWater - p->waterInjected;
   int wNeedTempo=p->waterNeeded;
   if(p->manualWater) wNeedTempo=p->manWaterpumped;
   
   if ( pumpW >= wNeedTempo || p->waterPres >= 750){
//     p->pumpOn=false;
     digitalWrite(p->pumpPin,LOW);
     p->pumpCount++;
   }
   else {
     digitalWrite(p->pumpPin,HIGH);      // turn pump on
     p->pumpCount = 0;
   }
   
   if(p->pumpCount>15){
     stopActuators(p);
     p->state=REACTING;
   }
   
 }
 
 /*------------------------------------------------------------------------------
 * void reacting(struct ALPS *p)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void reacting(struct ALPS *p){
//   int minTime = p->hours*60 + p->minutes;
   int rTime = reactinTime3;
   if (p->cycle <= 12) rTime = reactinTime2;
   if (p->cycle <= 6) rTime = reactinTime1;
   if (p->manualRTime) rTime = p->reactionTime;
   
   if ( p->minutes >= rTime){
     p->state=SUPPLYING;
     timeReset(p);
   }
 }
 
 
