/*------------------------------------------------------------------------------
 * void checkMode()
 * checks APLS systems mode
 *----------------------------------------------------------------------------*/
  void checkMode(){
    for(int i=0;i<ALPSnum;i++){
      if(alps[i].totalH2 >= h2expected) stopMode(&alps[i]);
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
   p->waterPumped=0;
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
 

