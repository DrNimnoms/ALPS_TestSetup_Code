/*------------------------------------------------------------------------------
 * void printout(void)
 * used for debuging 
 *----------------------------------------------------------------------------*/
 void serialEvent() {
  String inputString = "";
//  Serial.println("here");
  boolean stringComplete=false;
  while (Serial.available() ) {  //& !stringComplete
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
//  Serial.println(inputString);
  piCommand(inputString);
 }


/*------------------------------------------------------------------------------
 * void debugCommand(void)
 * does the command that is sent from the Raspberry pi
 *----------------------------------------------------------------------------*/
void piCommand(String input){
  int sval=input.indexOf("_");
  String stempo=input.substring(sval+1,sval+2);
  int sysnum=stempo.toInt();
  
  if(input.indexOf("time") >=0)//checks for on
  {
    int stime=input.indexOf(" ");
    String stempo2=input.substring(stime+1,sval);
    int tempoTime=stempo2.toInt();
    if(tempoTime>0){
      alps[sysnum].manualRTime=true;
      alps[sysnum].reactionTime=tempoTime;
      Serial.println(tempoTime);
    }
  }
  
  if(input.indexOf("notime") >=0)//checks for on
  {
    alps[sysnum].manualRTime=false;
  }
  
  if(input.indexOf("stream") >=0)//checks for on
  {
    alps[sysnum].stream=true;
  }
  
  if(input.indexOf("nodata") >=0)//checks for on
  {
    alps[sysnum].stream=false;
  }
  
  if(input.indexOf("run") >=0)//checks for on
  {
    runMode(&alps[sysnum]);
    alps[sysnum].stream=true;
  }
  
  if(input.indexOf("stop") >=0)//checks for on
  {
    stopMode(&alps[sysnum]);
  }
  
  if(input.indexOf("reset") >=0)//checks for on
  {
    reset(&alps[sysnum]);
  }
  
  if(input.indexOf("pump") >=0)//checks for on
  {
     stopActuators(&alps[sysnum]);
     alps[sysnum].state=PUMPING;
  }
  if(input.indexOf("inj") >=0)//checks for on
  {
     stopActuators(&alps[sysnum]);
     alps[sysnum].state=INJECTING;
  }
  if(input.indexOf("sup") >=0)//checks for on
  {
     stopActuators(&alps[sysnum]);
     alps[sysnum].state=SUPPLYING;
  }
  
  if(input.indexOf("react") >=0)//checks for on
  {
    stopActuators(&alps[sysnum]);
    alps[sysnum].state=REACTING;
  }
  
   if(input.indexOf("testp") >=0)//checks for on
  {
//    Serial.println("pump");
//    digitalWrite(POWERpin,HIGH);      // turn pump on
    digitalWrite(alps[sysnum].pumpPin,HIGH);      // turn pump on
    digitalWrite(alps[sysnum].waterVPin,HIGH);      // turn water valve on
  }
  if(input.indexOf("testi") >=0)//checks for on
  {
//    Serial.println("inject");
    digitalWrite(alps[sysnum].injectorVPin,HIGH);      // turn water injection valve on
  }
  if(input.indexOf("tests") >=0)//checks for on
  {
//    Serial.println("supply");
    alps[sysnum].supplyOn=true;
    digitalWrite(alps[sysnum].reactorVPin,HIGH);      // turn reactor valve on
  }
  
  if(input.indexOf("off") >=0)//checks for on
  {
//    Serial.println("All OFF");
    stopActuators(&alps[sysnum]);
  }
  
  if(input.indexOf("pri") >=0)//checks for pwm
  {
    printOut(&alps[sysnum]);
  }
}

/*------------------------------------------------------------------------------
 * void printout(void)
 * prints information out on the screen
 *----------------------------------------------------------------------------*/
void printOut(struct ALPS *p){
  Serial.print("\n\tSystem ");
  Serial.print(p->sysNum+1);
  Serial.println("'s Measurements");
  Serial.print("Reactor temp: ");
  Serial.print(p->reactorTemp);
  Serial.print(" C \t");
  Serial.print("Reactor pres: ");
  Serial.print(p->reactorPres,0);
  Serial.print(" PSIG \t");
  Serial.print("water pres: ");
  Serial.print(p->waterPres,0);
  Serial.print(" PSIG \t");
  Serial.print("water temp: ");
  Serial.print(p->waterTemp);
  Serial.print(" C \t");
  Serial.print("water flow: ");
  Serial.print(p->waterFlow);
  Serial.println(" mL/min");
  Serial.print("H_2 pres: ");
  Serial.print(p->h2pres);
  Serial.print(" PSIG \t");
  Serial.print("H_2 temp: ");
  Serial.print(p->h2temp);
  Serial.print(" C \t");
  Serial.print("H_2 vol flow: ");
  Serial.print(p->h2vFlow);
  Serial.print(" LPM \t");
  Serial.print("H_2 mass flow: ");
  Serial.print(p->h2mFlow);
  Serial.println(" SLPM");
}
