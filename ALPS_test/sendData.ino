/*------------------------------------------------------------------------------
 * void sendData()
 * sends data 
 *----------------------------------------------------------------------------*/
void sendData(){
  for(int i=0;i<ALPSnum;i++){
    if(alps[i].stream){
      alps[i].commDt=(timeElapsed(alps[i].commTimeStamp)/1000.0); //milliseconds since last communication 
//      int minTime = alps[i].hours*60 + alps[i].minutes;
      if((alps[i].state == REACTING || alps[i].mode == STOP) && alps[i].minutes >= 20){
        if(alps[i].commDt >= reactionRTime) {
          alps[i].commTimeStamp=micros();
          sendAlpsData(&alps[i]); 
        } 
      }
      else{
        alps[i].commTimeStamp=micros();
        sendAlpsData(&alps[i]); 
      }
    }
  }
}  


/*------------------------------------------------------------------------------
 * void sendAlpsData(struct ALPS *p)
 * sends information for one alps system
 *----------------------------------------------------------------------------*/
void sendAlpsData(struct ALPS *p){
  
  Serial.print(p->sysNum);
  Serial.print(',');
  Serial.print(p->commDt,0);
  Serial.print(',');
//  Serial.print(p->mode);
//  Serial.print(',');
  Serial.print(p->state);
  Serial.print(',');
  Serial.print(p->cycle);
  Serial.print(',');
  Serial.print(p->reactorPres);
  Serial.print(',');
  Serial.print(p->waterPres);
  Serial.print(',');
  Serial.print(p->reactorTemp,0);
  Serial.print(',');
  Serial.print(p->waterTemp,0);
  Serial.print(',');
  Serial.print(p->h2temp,0);
  Serial.print(',');
  Serial.print(p->h2pres);
  Serial.print(',');
  Serial.print(p->h2mFlow);
  Serial.print(',');
  Serial.print(p->totalWater,0);
  Serial.print(',');
  Serial.println(p->totalH2);
}

