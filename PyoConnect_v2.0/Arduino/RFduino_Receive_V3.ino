#include <RFduinoBLE.h>

//*********************************************************************************
//Definitions
//*********************************************************************************

#define highEMG             300            //people with high EMG activity // was 550
#define lowEMG              100            //people with low EMG activity
#define MAX_LED             5              //set the maximum number of LEDs
#define ThresholdVAL        4              //sets the LED to activate the TENS device
#define minimumLow          80             //minimum values desired from Myo for consideration for Low EMG
#define minimumHigh         100            //minimum values desired from Myo for consideration for High EMG
#define outputActive        1              //To TENS device; output on digital GPIO_pin_2
#define SwitchThresholdPin  0              //pushbutton to select threshold based on EMG signal strength, GPIO_pin_1
#define _MAX(a,b)  ((a) > (b) ? (a) : (b))

int avgFingers_sensorVal[3];                  //Average EMG activity read for fingers movement - sensors 1,6
int avgArm_sensorVal[4];                      //Average EMG activity read for Arm movement - sensors 3,4,5,6,8
int avgLeft_sensorVal[2];                     //Average EMG activity read for Left movement - sensors 1,2
int avgRight_sensorVal[3];                    //Average EMG activity read for right movement - sensors 5,6


int AverageFingers, AverageArm, AverageLeft, AverageRight;
int finalReadingFingers, finalReadingArm, finalReadingLeft, finalReadingRight;
int MAX = 0;
int minimumValue = 0;
int SwitchThresholdState = 0;
byte valFingers = 0;                       //LEDs - EMG ratio
byte valArm     = 0;
byte valLeft    = 0;
byte valRight   = 0;
byte multiplier = 1;                       //EMG multiplier
byte tensPin[] = {2, 3, 4, 5, 6};          //To show EMG strength



//*********************************************************************************
//Setup: only run once
//*********************************************************************************
void setup()
{
  // Set tenPins as outputs.
  for (int i=0; i<MAX_LED; i++){
    pinMode(tensPin[i], OUTPUT);    
  }
  pinMode(outputActive,OUTPUT);
  pinMode(SwitchThresholdPin, INPUT);     //GPIO 0, switch between threshholds

  /* Enable serial debug.
   * Sending a lot of data at baud rates faster than 9600 when the BLE is enabled causes overflow errors.
   * this constraint is overridden to allow higher baudrates
   */
  override_uart_limit = true; 
  //Serial.begin(115200);               // begin serial debug
  Serial.println("Welcome!!! Human-Human Interface");
  Serial.println("RFduino example started");
  Serial.println("Serial rate set to 115200 baud");

  // All LEDs are initially turned off
  for (int i=0; i<MAX_LED; i++){
    digitalWrite(tensPin[i],LOW);
  }
  digitalWrite(outputActive,LOW); 

  // Indicate that LEDs are operational to user.
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(tensPin[i], HIGH);
    delay (500);
  }

  // LEDs are turned-off and shall be activated by EMG signal strength
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(tensPin[i], LOW);
    delay (500);
  }
  
  /*
   * Configuration for RFduino and Bluetooth services
   * deviceName, advertise/interval, switch to LE mode
   */
  RFduinoBLE.deviceName = "RFduino";
  RFduinoBLE.advertisementData = "data";
  RFduinoBLE.advertisementInterval = MILLISECONDS(300);
  RFduinoBLE.txPowerLevel = -20;  // (-20dbM to +4 dBm)
  Serial.println("RFduino BLE Advertising interval is 300ms");
  Serial.println("RFduino BLE DeviceName: RFduino");
  Serial.println("RFduino BLE Tx Power Level: -20dBm");
  
  // start the BLE stack
  RFduinoBLE.begin();
  Serial.println("RFduino BLE stack started");

   MAX  = highEMG;              //People with high EMG activity set as default
   minimumValue = minimumHigh;  //Minimum value required from sensor, set to high
}


//*********************************************************************************
//
//*********************************************************************************
void loop()
{
  // switch to lower power mode
  RFduino_ULPDelay(INFINITE);  
}


//*********************************************************************************
//Callback function on advertisement / on connect / on disconnect
//*********************************************************************************
void RFduinoBLE_onAdvertisement(bool start)
{
  Serial.println("RFduino is doing BLE advertising ...");
}

void RFduinoBLE_onConnect()
{
  Serial.println("RFduino BLE connection successful");
}

void RFduinoBLE_onDisconnect()
{
  Serial.println("RFduino BLE disconnected");
  digitalWrite(outputActive, LOW);
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(tensPin[i], LOW);
    delay (500);
  }
}

//*********************************************************************************
//Callback function on receive data
//*********************************************************************************
void RFduinoBLE_onReceive(char *data, int len)
{
  SwitchThresholdState = digitalRead(SwitchThresholdPin); // Get switch status: switching thresholds  
  if (SwitchThresholdState == HIGH){                      // This will allow the switching between a low threshold and high threshold state on Switch1 - S1
    if(MAX == highEMG){ 
       MAX = lowEMG; 
       minimumValue = minimumLow;
       digitalWrite(tensPin[3],HIGH); 
       digitalWrite(tensPin[4],LOW);
    } 
    else{
      MAX = highEMG; 
      minimumValue = minimumHigh;
      digitalWrite(tensPin[4],HIGH); 
      digitalWrite(tensPin[3],LOW);
    } 
     
    while (SwitchThresholdState == HIGH) { // This will pause the program while the person is touching the threshold button, 
        SwitchThresholdState = digitalRead(SwitchThresholdPin);        
        delay(10); 
    }// so it doesn't flip back and forth while button is pushed
  }
  
  /* // Not enough pins: Therefore, implemented manually outside of microcontroller
  SwitchState = digitalRead(SwitchStatePin);
  if (SwitchState == HIGH){ // This will activate the TENS if the PushButton is pressed on S1
    digitalWrite(TENS_StimulPin, HIGH); 
    //digitalWrite(aQ1, HIGH);
  }
  while (SwitchState == HIGH) { // This will pause the program while the person is touching TENS test button
      SwitchState = digitalRead(SwitchStatePin); 
      digitalWrite(TENS_StimulPin, HIGH); 
      delay(10); 
  }*/
 
  Serial.println("Received data over BLE");

/*  // just for viewing Myo signals****************************************
  uint8_t a,b,c,d,e,f,g,h; 
  a = data[0]; Serial.print(a); Serial.print("\t");
  b = data[1]; Serial.print(b); Serial.print("\t");
  c = data[2]; Serial.print(c); Serial.print("\t");
  d = data[3]; Serial.print(d); Serial.print("\t");
  e = data[4]; Serial.print(e); Serial.print("\t");
  f = data[5]; Serial.print(f); Serial.print("\t");
  g = data[6]; Serial.print(g);Serial.print("\t");
  h = data[7]; Serial.println(h);*/
  //**********************************************************************

  // Clear User Variables
  ClearVariables();

  //*****************Implementation starts here***************************
  uint8_t accFingers1[10], accFingers2[10], accFingers3[10];
  uint8_t accArm1[10], accArm2[10], accArm3[10], accArm4[10];
  uint8_t accLeft1[10], accLeft2[10];
  uint8_t accRight1[10], accRight2[10], accRight3[10];

  uint8_t myo1_sen, myo2_sen, myo3_sen, myo4_sen, myo5_sen, myo6_sen, myo7_sen, myo8_sen;
  myo1_sen = data[0]; 
  myo2_sen = data[1]; 
  myo3_sen = data[2]; 
  myo4_sen = data[3]; 
  myo5_sen = data[4]; 
  myo6_sen = data[5]; 
  myo7_sen = data[6]; 
  myo8_sen = data[7];

  // *****************Fingers Actuation***********************************
  if((myo1_sen >= minimumValue) && (myo6_sen >= minimumValue)){
    myo2_sen = myo3_sen = myo4_sen = myo5_sen = myo7_sen = myo8_sen = 1;
    
    //Take 10 EMG readings in 0.001 seconds
    for(int index=0; index<10; index++){
      accFingers1[index] = myo1_sen * multiplier;
      accFingers2[index] = myo6_sen * multiplier;   
    }
    
     //Take average of the 10 readings
    for(int i = 0; i < 10; i++){
      avgFingers_sensorVal[0] +=  accFingers1[i];
      avgFingers_sensorVal[1] +=  accFingers2[i];
    }
    
    AverageFingers      = (avgFingers_sensorVal[0] + avgFingers_sensorVal[1])/18;

    finalReadingFingers = constrain(AverageFingers, 0, MAX);                // constrain Average value to MAX
    valFingers          = map(finalReadingFingers,  0, MAX,0, MAX_LED);     // Map final reading to MAX_LED
  }
  else{
    valFingers = 0;
  }


  // ********************Arm Actuation***********************************
  if((myo3_sen >= minimumValue) && (myo4_sen >= minimumValue) && (myo5_sen >= minimumValue) && (myo6_sen >= minimumValue)){
    myo1_sen = myo2_sen = myo7_sen = myo8_sen = 1;
    
    //Take 10 EMG readings in 0.001 seconds
    for(int index=0; index<10; index++){
      accArm1[index]     = myo3_sen * multiplier;
      accArm2[index]     = myo4_sen * multiplier;
      accArm3[index]     = myo5_sen * multiplier;
      accArm4[index]     = myo6_sen * multiplier;
    }
    
     //Take average of the 10 readings
    for(int i = 0; i < 10; i++){
      avgArm_sensorVal[0]     +=  accArm1[i];
      avgArm_sensorVal[1]     +=  accArm2[i];
      avgArm_sensorVal[2]     +=  accArm3[i];
      avgArm_sensorVal[3]     +=  accArm4[i];
    }

    AverageArm          = (avgArm_sensorVal[0] + avgArm_sensorVal[1] + avgArm_sensorVal[2] + avgArm_sensorVal[3])/40;

    finalReadingArm     = constrain(AverageArm,     0, MAX);                // constrain Average value to MAX
    valArm              = map(finalReadingArm,      0, MAX,0, MAX_LED);     // Map final reading to MAX_LED
  }
  else{
    valArm = 0;
  }


  // ********************Left Actuation***********************************
  if((myo1_sen >= minimumValue) && (myo2_sen >= minimumValue)){
     myo3_sen = myo4_sen = myo5_sen = myo6_sen =myo7_sen = myo8_sen = 1;
    
    //Take 10 EMG readings in 0.001 seconds
    for(int index=0; index<10; index++){
      accLeft1[index]    = myo1_sen * multiplier;
      accLeft2[index]    = myo2_sen * multiplier;
    } 

    //Take average of the 10 readings
    for(int i = 0; i < 10; i++){
      avgLeft_sensorVal[0]    +=  accLeft1[i];
      avgLeft_sensorVal[1]    +=  accLeft2[i];
    }

    AverageLeft         = (avgLeft_sensorVal[0] + avgLeft_sensorVal[1])/20;

    finalReadingLeft    = constrain(AverageLeft,    0, MAX);                // constrain Average value to MAX
    valLeft             = map(finalReadingLeft,     0, MAX,0, MAX_LED);     // Map final reading to MAX_LED
  }
  else{
    valLeft = 0;
  }


  // *****************Right Actuation***********************************
  if((myo5_sen >= minimumValue) && (myo6_sen >= minimumValue) && (myo7_sen >= minimumValue)){
     myo1_sen = myo2_sen = myo3_sen = myo4_sen =myo8_sen = 1;
     
    //Take 10 EMG readings in 0.001 seconds
    for(int index=0; index<10; index++){
      accRight1[index]   = myo5_sen * multiplier;
      accRight2[index]   = myo6_sen * multiplier;
      accRight3[index]   = myo7_sen * multiplier;
    }

    //Take average of the 10 readings
    for(int i = 0; i < 10; i++){
      avgRight_sensorVal[0]   +=  accRight1[i];
      avgRight_sensorVal[1]   +=  accRight2[i];
      avgRight_sensorVal[2]   +=  accRight3[i];
    }  

    AverageRight        = (avgRight_sensorVal[0] + avgRight_sensorVal[1] + avgRight_sensorVal[2])/25;

    finalReadingRight   = constrain(AverageRight,   0, MAX);                // constrain Average value to MAX
    valRight            = map(finalReadingRight,    0, MAX,0, MAX_LED);     // Map final reading to MAX_LED
    
  }
  else{
    valRight = 0;
  }
   
  /*
  Serial.print(AverageFingers); Serial.print("\t");
  Serial.print(AverageArm);     Serial.print("\t");
  Serial.print(AverageLeft);    Serial.print("\t");
  Serial.print(AverageRight);   Serial.print("\n");
  
  Serial.print(valFingers); Serial.print("\t");
  Serial.print(valArm);     Serial.print("\t");
  Serial.print(valLeft);    Serial.print("\t");
  Serial.print(valRight);   Serial.print("\n");*/
  
 
 for(int thisLED = 0; thisLED < 3; thisLED++){                     //write all LEDs low and stim pin low
    digitalWrite(tensPin[thisLED], LOW);
    digitalWrite(outputActive, LOW);  
  }
  

  // *****************Decide on Actuation********************************
  int actuate;
  int biggest = _MAX(_MAX(valFingers,valArm),_MAX(valLeft,valRight));
  if(biggest == valFingers){
    actuate = 1;
  }else if(biggest == valArm){
    actuate = 2;
  }else if(biggest == valLeft){
    actuate = 3;
  }else if(biggest == valRight){
    actuate = 4;
  }else{
    actuate = 0;
  }

  // *****************   Actuation   ***********************************
  switch(actuate){
      case 0:  
        digitalWrite(tensPin[0], LOW);
        digitalWrite(tensPin[1], LOW);
        digitalWrite(tensPin[2], LOW);     
      break;

      case 1:
        if(valFingers >= ThresholdVAL){
          //digitalWrite(outputActive,HIGH);
          digitalWrite(tensPin[0], LOW);
          digitalWrite(tensPin[1], LOW);
          digitalWrite(tensPin[2], LOW);
          //Serial.println("Fingers");
          //delay(1);
        } 
      break;

      case 2:
        if(valArm >= ThresholdVAL){                    
          digitalWrite(tensPin[0], HIGH);
          //digitalWrite(outputActive,HIGH);
          digitalWrite(tensPin[1], LOW);
          digitalWrite(tensPin[2], LOW);
          //Serial.println("Arm");
          delay(20);
        }
      break;

      case 3:
        if(valLeft >= ThresholdVAL){                    
          digitalWrite(tensPin[1], HIGH);
          //digitalWrite(outputActive,HIGH);
          digitalWrite(tensPin[0], LOW);
          digitalWrite(tensPin[2], LOW);
          //digitalWrite(tensPin[3], LOW);
          //Serial.println("Left");
          delay(20);
        }
        //else
          //digitalWrite(tensPin[2], LOW);
      break;

      case 4:
        if(valRight >= ThresholdVAL){                    
          digitalWrite(tensPin[2], HIGH);
          //digitalWrite(outputActive,HIGH);
          digitalWrite(tensPin[0], LOW);
          digitalWrite(tensPin[1], LOW);
          //Serial.println("Right");
          delay(20);
        }
      break;

      default:
        digitalWrite(tensPin[0], LOW);
        digitalWrite(tensPin[1], LOW);
        digitalWrite(tensPin[2], LOW);
      break;
 }

  for (int i=0; i<8; i++){
     data[i]= 0; 
  }

  Serial.flush();

}

void ClearVariables()
{
   // *****************Reset Variables***********************************
   for (int i = 0; i < 4; i++)
   {
    if (i < 3){
      avgFingers_sensorVal[i] = 0;                  
      avgArm_sensorVal[i] = 0;                     
      avgLeft_sensorVal[i] = 0;                     
      avgRight_sensorVal[i] = 0;
    } 
    else 
     avgArm_sensorVal[i]; 
   }
  AverageFingers = AverageArm = AverageLeft = AverageRight = 0;  
}

