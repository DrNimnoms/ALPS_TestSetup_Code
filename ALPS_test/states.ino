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
      case INJECTING:
        inject(p);
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
   digitalWrite(p->pumpPin,HIGH);      // turn pump on
   digitalWrite(p->waterVPin,HIGH);      // turn water valve on
   float pumpW=(*p).totalWater - (*p).waterPumped;
   if ( pumpW >= p->waterNeeded){
     stopActuators(p);
     p->state=SUPPLYING;
     timeReset(p);
   }
 }
 
  /*------------------------------------------------------------------------------
 * void supply(struct ALPS *p, int h2vpin)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void supply(struct ALPS *p){

   p->countH2=true;
   digitalWrite(p->reactorVPin,HIGH);      // turn reactor valve on   
   
   if ( p->reactorPres <= minPres){
     stopActuators(p);
     p->countH2=false;
     p->state=INJECTING;
     p->cycle++;
     p->waterNeeded += waterNeededRate;
     p->waterNeeded=min(p->waterNeeded,waterNeededMax);
     timeReset(p);
   }
 }
 
  /*------------------------------------------------------------------------------
 * void inject(struct ALPS *p, int watervpin)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void inject(struct ALPS *p){

   digitalWrite(p->injectorVPin,HIGH);      // turn water injection valve on
   
   if ( p->reactorPres >= p->waterPres){
     stopActuators(p);
     p->state=PUMPING;
     timeReset(p);
   }
 }
 
 
 /*------------------------------------------------------------------------------
 * void pump(struct ALPS *p, int pumpPin, int h2vpin)
 * initializes the reaction 
 *----------------------------------------------------------------------------*/
 void pump(struct ALPS *p){
   
//   p->pumpOn=true;
   digitalWrite(p->pumpPin,HIGH);      // turn pump on
   digitalWrite(p->waterVPin,HIGH);      // turn water valve on
   float pumpW=p->totalWater - p->waterPumped;
   if ( pumpW >= p->waterNeeded || p->waterPres >= 750){
//     p->pumpOn=false;
     digitalWrite(p->pumpPin,LOW);
     p->pumpCount++;
   }
   else p->pumpCount = 0;
   if(p->pumpCount>10){
     stopActuators(p);
     p->waterPumped=p->totalWater;
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
   
   if (p->reactorPres >= maxPres + 5){
     p->countH2=true;
     digitalWrite(p->reactorVPin,HIGH);      // turn reactor valve on   
   }
   else if(p->reactorPres <= maxPres - 5){
     p->countH2=false;
     digitalWrite(p->reactorVPin,LOW);
   }
   
   if ( p->minutes >= rTime){
     p->state=SUPPLYING;
     timeReset(p);
   }
 }
 
 
