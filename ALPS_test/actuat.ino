// /*------------------------------------------------------------------------------
// * void stopMode(struct ALPS *p)
// * starts the APLS system reactor
// *----------------------------------------------------------------------------*/
// void actuat(){
//   for(int i=0;i<ALPSnum;i++){
//      if(alps[i].pumpOn) turnPumpOn(&alps[i]);
//      else{
//        alps[i].actuatTimeStamp = micros();
//        turnPumpOff(&alps[i]);
//      }
//      if(alps[i].injectOn) digitalWrite(p->injectorVPin,HIGH);      // turn injector valve on
//      else digitalWrite(p->injectorVPin,LOW);      // turn injector valve off
//      if(alps[i].supplyOn) digitalWrite(p->reactorVPin,HIGH);      // turn reactor valve on
//      else digitalWrite(p->reactorVPin,LOW);      // turn reactor valve off
//    }
// }
// 
// 
// /*------------------------------------------------------------------------------
// * void stopMode(struct ALPS *p)
// * starts the APLS system reactor
// *----------------------------------------------------------------------------*/
// 
 /*------------------------------------------------------------------------------
 * void stopMode(struct ALPS *p)
 * stops all actuators
 *----------------------------------------------------------------------------*/
 void stopActuators(struct ALPS *p){
   digitalWrite(POWERpin,LOW);
   digitalWrite(p->pumpPin,LOW);      // turn pump off
   digitalWrite(p->waterVPin,LOW);      // turn water valve off
   digitalWrite(p->injectorVPin,LOW);      // turn injector valve off
   digitalWrite(p->reactorVPin,LOW);      // turn reactor valve off
 }
