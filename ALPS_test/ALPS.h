/*------------------------------------------------------------------------------
 * ALPS.h
 * Created by Nima Ghods
 * Data: 9/5/2014
 * setsup the constants and parameters for ALPS_XX.ino
 *----------------------------------------------------------------------------*/

// ALPS parameters
  #define ALPSnum 2       // number of reactors
  #define h2expectedR1 750  // 95% of the expected hydrogen production
  #define h2expectedR2 855  // 95% of the expected hydrogen production
  #define minPres 300      // minimum reactor pressure in PSI
  #define maxPres 1000    // maximum reactor pressure in PSI
  #define reactinTime1 120  // reaction time in minutes
  #define reactinTime2 240  // reaction time in minutes
  #define reactinTime3 420  // reaction time in minutes
  #define waterNeededMin 25 // water added per reaction in ml
  #define waterNeededMax 55 // water added per reaction in ml
  #define waterNeededRate 10 // water added per reaction in ml
  #define reactionRTime 60000//time (microsec) between sending data while in REACTION state
  #define wait1Time 2        // wait time (minutes) between supplying and injection 
  #define wait2Time 2        // wait time (minutes) between injection and pumping

// actuator pins
  #define POWERpin 29    // water pump power pin

  #define WATERv1 37     // water valve pin
  #define INJECTv1 36  // reactor valve pin
  #define REACTORv1 35        // hydrogen valve pin
  #define PUMPpin1 26    // water pump pin
  
  #define WATERv2 34     // water valve pin
  #define INJECTv2 33  // reactor valve pin
  #define REACTORv2 32   // hydrogen valve pin
  #define PUMPpin2 25    // water pump pin

// Sensor pins
  #define REACTORt1 A11  // reactor temperature sensor pin
  #define REACTORp1 A1   // reactor pressure sensor pin
  #define WATERp1 A4      // water pressure sensor pin
  #define WATERf1 A9      // water flow sensor pin
  #define WATERt1 A13      // water flow sensor pin
  
  #define REACTORt2 A12  // reactor temperature sensor pin
  #define REACTORp2 A3   // reactor pressure sensor pin
  #define WATERp2 A2      // water pressure sensor pin
  #define WATERf2 A9     // water flow sensor pin
  #define WATERt2 A14      // water flow sensor pin

// ADC conversion constants
  #define presConst  1.955       // convert adc value to PSIG ==> press= adc *(2000 psig/1023)
  #define waterFlowConst 0.48876 // convert adc value to ml/min ==> flow= adc *(500 ml/min/1023)
  #define tempConst 0.48876      // convert adc value to C ==> temp= adc *(500 C/1023)

//time
  #define FIVEMINUTE 300000000  // in microseconds
  #define TWOMINUTE 120000000  // in microseconds
  #define ONEMINUTE 60000000  // in microseconds
  #define ONESECOND 1000000   // in microseconds

// debugging variables
  boolean uartPrint=false;    // print for debugging

// loop timing variables
  const long controlTime=150000;          // loop time in uSec  .2 s loops ==> 5Hz
  const float dt=controlTime/1000000.0;   // control time in sec
  const float dtm=controlTime/1000000.0/60.0;   // control time in sec times minute
  unsigned long timeStamp=0;              // used to keep track of the loop time

// ALPS system variables
  enum sysMode {STOP, RUN};
  enum sysState {INITALIZING, SUPPLYING, WAIT1, INJECTING, WAIT2, PUMPING, REACTING};
  boolean pumpPower=false;
  typedef struct ALPS {
    // end condation
    int h2expected;
    // actuator pins
    int pumpPin;
    int waterVPin;
    int injectorVPin;
    int reactorVPin;
    // actuator states
    boolean pumpOn;
    boolean injectOn;
    boolean supplyOn;
    int pumpCount;
    // sensor pins
    int reactorTPin;
    int reactorPPin;
    int waterPPin;
    int waterFPin;
    int waterTPin;
    // data
    int sysNum;
    sysMode mode;
    sysState state;
    float reactorTemp;
    float reactorPres;
    float waterPres;
    float waterFlow;
    float waterTemp;
    float h2pres;
    float h2temp;
    float h2vFlow;
    float h2mFlow;
    float reactorLPres;
    float reactorDPres;
    float totalWater;
    float totalH2;
    boolean countH2;
    float waterInjected;
    int waterNeeded;
    int cycle;
    unsigned long commTimeStamp;
    float commDt;
//    int hours;
    int minutes;
    unsigned long microseconds;
    unsigned long timeKeepingStamp;
    boolean stream;
    boolean manualRTime;
    boolean manualWater;
    int manWaterpumped;
    int reactionTime;
  } ALPSsys;
  
  ALPSsys alps[ALPSnum];

