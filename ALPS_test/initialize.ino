/*------------------------------------------------------------------------------
 * void Inital(void)
 * initializes the pins as inputs and outputs and sets up serial communication
 *----------------------------------------------------------------------------*/

void Inital(void){
  
  int i=0;
  
  Serial.begin(115400);           // set up Serial library at 115400 bps 
//  Serial.begin(19200);           // set up Serial library at 19200 bps 
  
  h2_setup();                // set up hydrogen sensor
  
  //assign actuator pins
  alps[0].pumpPin=PUMPpin1;
  alps[0].waterVPin=WATERv1;
  alps[0].injectorVPin=INJECTv1;
  alps[0].reactorVPin=REACTORv1;
  
  alps[1].pumpPin=PUMPpin2;
  alps[1].waterVPin=WATERv2;
  alps[1].injectorVPin=INJECTv2;
  alps[1].reactorVPin=REACTORv2;
  
  //assign sensor pins
  alps[0].reactorTPin=REACTORt1;
  alps[0].reactorPPin=REACTORp1;
  alps[0].waterPPin=WATERp1;
  alps[0].waterFPin=WATERf1;
  alps[0].waterTPin=WATERt1;
  
  alps[1].reactorTPin=REACTORt2;
  alps[1].reactorPPin=REACTORp2;
  alps[1].waterPPin=WATERp2;
  alps[1].waterFPin=WATERf2;
  alps[1].waterTPin=WATERt2;
  
  // end condation
  alps[0].h2expected=h2expectedR1;
  alps[1].h2expected=h2expectedR2;
  
  // setup digital I/Os
  for(i=0;i<ALPSnum;i++){
    relay_setup(alps[i].pumpPin);
    relay_setup(alps[i].waterVPin);
    relay_setup(alps[i].injectorVPin);
    relay_setup(alps[i].reactorVPin);
  }
  
  //get initial sensor values
  measNcal();
  
  for(i=0;i<ALPSnum;i++){
    alps[i].sysNum=i;  // set the system number  
    alps[i].pumpOn=false;
    alps[i].injectOn=false;
    alps[i].supplyOn=false;
    reset(&alps[i]);   // reset alps system
    alps[i].mode=STOP; //set the system to stop mode
    alps[i].stream=false;  // sets the stream data to false 
    alps[i].countH2=false;
    alps[i].manualRTime=false;
  }
//  alps[0].cycle=13;
//  alps[0].totalWater=1498;
//  alps[0].totalH2=434.43;
//  alps[0].waterPumped=alps[0].totalWater;
//  alps[0].waterNeeded=waterNeededMax;
//  alps[0].state=SUPPLYING;
  delay(500);
}


/*------------------------------------------------------------------------------
 * void relay_setup(int relayPin)
 * setup relay
 *----------------------------------------------------------------------------*/
  void relay_setup(int relayPin)
  {
    pinMode(relayPin, OUTPUT);     //pin selected to be output 
    digitalWrite(relayPin,LOW);    //pin output set to 0
  }
