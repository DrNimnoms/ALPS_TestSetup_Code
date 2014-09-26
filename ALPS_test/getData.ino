/*------------------------------------------------------------------------------
 * void measNcal(void)
 * Measures all sensor and calculates needed values on the ALPS system
 *-----------------------------------------------------------------------------*/
 void measNcal(void){
  int i=0;
  static unsigned long waitTimeStamp[ALPSnum]={0};
  h2_rdata();    // start hydrogen pulling
  for(i=0;i<ALPSnum;i++)
  {
    alps[i].reactorLPres=alps[i].reactorPres;    
    alps[i].reactorPres=avgADC(alps[i].reactorPPin,2)*presConst;  // get reactor pressure
    alps[i].reactorTemp=avgADC(alps[i].reactorTPin,1)*tempConst;  // get reactor temperature
    alps[i].waterPres=avgADC(alps[i].waterPPin,2)*presConst;      // get water pressure
    alps[i].waterFlow=avgADC(alps[i].waterFPin,2)*waterFlowConst; // get water flow
    alps[i].waterTemp=avgADC(alps[i].waterTPin,1)*tempConst;      // get water temperature
    
    alps[i].reactorDPres = rateCal(alps[i].reactorPres,alps[i].reactorLPres);  // calculate reactor pressure rate 
//    if(alps[i].state==INITALIZING || alps[i].state==PUMPING) 
    alps[i].totalWater += alps[i].waterFlow*dtm;         //calculate totalwater pumped
   
    stateTime(&alps[0]);
  }
  h2_gdata(&alps[0]);
  for(i=0;i<ALPSnum;i++){
   if(alps[i].countH2) //alps[i].state==SUPPLYING
   { 
     waitTimeStamp[i]=micros();
     alps[i].totalH2 += alps[i].h2mFlow*dtm;
   }
   else if(!areWeThereYet(waitTimeStamp[i],TWOMINUTE)) alps[i].totalH2 += alps[i].h2mFlow*dtm;
  }
  
 }
 
/*------------------------------------------------------------------------------
 * int avgADC(int adcPin,int n)
 * average the ADC measurement 2^n times
 * returns the average measurement
 *-----------------------------------------------------------------------------*/
 int avgADC(int adcPin,int n){
  long tempo=0;
  for(int i=0;i<(1<<n);i++){
    tempo+=analogRead(adcPin);
    delay(1);
  }
  tempo=tempo>>n;
  return (int)tempo;
 }
 
/*------------------------------------------------------------------------------
 *  float rateCal(float value, float valueLast)
 * takes in the current and last data point
 * returns the rate
 *-----------------------------------------------------------------------------*/
 float rateCal(float value, float valueLast){
   float valueRate=0;
   valueRate=(value-valueLast)/dt;
   
   return valueRate;
 }
 
