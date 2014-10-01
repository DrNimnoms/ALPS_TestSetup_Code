/*------------------------------------------------------------------------------
 * void h2_setup()
 * setup the H2 flowmeter
 *----------------------------------------------------------------------------*/
  void h2_setup()
  {
    int brate=19200;//38400
    Serial1.begin(brate,SERIAL_8N1); 
    delay(200);
    Serial2.begin(brate,SERIAL_8N1); 
    delay(200);
  }

/*------------------------------------------------------------------------------
 * void h2_data()
 * request data from H2 flowmeter
 *----------------------------------------------------------------------------*/
  void h2_rdata()
  {
    Serial1.print("a\r");
    Serial2.print("a\r");
  }

/*------------------------------------------------------------------------------
 * void h2_data()
 * gets data from H2 flowmeter
 *----------------------------------------------------------------------------*/
  void h2_gdata1(struct ALPS *p)
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
      p->h2pres = data[0];
      p->h2temp = data[1];
      p->h2vFlow = data[2];
      p->h2mFlow = data[3];
    }
  }
  
  /*------------------------------------------------------------------------------
 * void h2_data()
 * gets data from H2 flowmeter
 *----------------------------------------------------------------------------*/
  void h2_gdata2(struct ALPS *p)
  {
    boolean done=false;
    int sVal=0;
    int eVal=0;
    String aliData="";
    String tempo1="";
    String tempo2="";
    float data[4]={0};
    if (Serial2.available()) {
      while (!done) {
        char inByte = (char)Serial2.read();
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
      p->h2pres = data[0];
      p->h2temp = data[1];
      p->h2vFlow = data[2];
      p->h2mFlow = data[3];
    }
  }
