/*------------------------------------------------------------------------------
 * void h2_setup()
 * setup the H2 flowmeter
 *----------------------------------------------------------------------------*/
  void h2_setup()
  {
    Serial1.begin(19200,SERIAL_8N1); 
    delay(500);
  }

/*------------------------------------------------------------------------------
 * void h2_data()
 * request data from H2 flowmeter
 *----------------------------------------------------------------------------*/
  void h2_rdata()
  {
    Serial1.print("a\r");
  }

/*------------------------------------------------------------------------------
 * void h2_data()
 * gets data from H2 flowmeter
 *----------------------------------------------------------------------------*/
  void h2_gdata(struct ALPS *alpstemp)
  {
    boolean done=false;
    int sVal=0;
    int eVal=0;
    String aliData="";
    String tempo1="";
    String tempo2="";
    float data[4]={0};
    if (Serial1.available()) {
      while (!done) {
        char inByte = (char)Serial1.read();
        aliData += inByte;
        if (aliData.indexOf("H2")>=0) done=true;
        else delay(1);
      }
  //    Serial.println(aliData);
      eVal=aliData.indexOf("H2");
      for(int i=0;i<4;i++){
        sVal=aliData.indexOf("+");
        aliData=aliData.substring(sVal+1,eVal-1);
        tempo1=aliData.substring(0,3);
        tempo2=aliData.substring(4,6);
        data[i]=tempo1.toInt()+tempo2.toInt()/100.0;
      }
      (*alpstemp).h2pres = data[0];
      (*alpstemp).h2temp = data[1];
      (*alpstemp).h2vFlow = data[2];
      (*alpstemp).h2mFlow = data[3];
    }
  }
