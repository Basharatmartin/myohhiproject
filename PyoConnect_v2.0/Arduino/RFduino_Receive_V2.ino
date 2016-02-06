/*********************************************************************************
\file:  RFduino_Recieve_V2.ino

\DESCRIPTION:
          -This file is part of our wearable lab project
          -Realizes only one movement of the hand

\n Copyright (c) wearable lab
\n Date: 09.01.2016
\n Boniface Bassey
*********************************************************************************/

#include <RFduinoBLE.h>

//*********************************************************************************
//Definitions
//*********************************************************************************

#define highEMG             550            //people with high EMG activity
#define lowEMG              300            //people with low EMG activity
#define MAX_LED             5              //set the maximum number of LEDs
#define ThresholdVAL        3              //sets the LED to activate the TENS device
#define TENS_StimulPin      1              //To TENS device; output on digital GPIO_pin_2
#define SwitchThresholdPin  0              //pushbutton to select threshold based on EMG signal strength, GPIO_pin_1

int avgSensor1;
int avgSensor2;
int avgSensor3;                             //Average EMG activity read
int avgSensor4;
int AverageEMG;
int finalReading;
int MAX = 0;
int SwitchThresholdState = 0;
byte level = 0;                             //LEDs - EMG ratio
byte multiplier = 1;                        //EMG multiplier
byte LEDs[] = {2,3, 4, 5, 6};               //To show EMG strength



//*********************************************************************************
//Setup: only run once
//*********************************************************************************
void setup()
{
  // Set pins as outputs.
  for (int i=0; i<MAX_LED; i++){
    pinMode(LEDs[i], OUTPUT);    
  }
  pinMode(TENS_StimulPin, OUTPUT);        //set TENS device output to TENS_StimulPin on 2
  pinMode(SwitchThresholdPin, INPUT);     //GPIO 0, switch between threshholds

  /* Enable serial debug.
   * Sending a lot of data at baud rates faster than 9600 when the BLE is enabled causes overflow errors.
   * this constraint is overridden to allow higher baudrates
   */
  override_uart_limit = true;
  
  //Serial.begin(115200);               // begin serial debug
  Serial.print("\n");
  Serial.println("***Welcome!!! Human-Human Interface***");
  Serial.println("RFduino example started");
  Serial.println("Serial rate set to 115200 baud");

  // All LEDs are initially turned off
  for (int i=0; i<MAX_LED; i++){
    digitalWrite(LEDs[i],LOW);
  }

  // Indicate that LEDs are operational to user.
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(LEDs[i], HIGH);
    delay (500);
  }

  // LEDs are turned-off and shall be activated by EMG signal strength
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(LEDs[i], LOW);
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

   MAX  = highEMG; //People with high EMG activity set as default
}


//*********************************************************************************
//
//*********************************************************************************
void loop()
{
  // switch to lower power mode
  RFduino_ULPDelay(INFINITE);  

  // to send one char
  // RFduinoBLE.send((char)temp);
 
  // to send multiple chars
  // RFduinBLE.send(&data, len);
}


//*********************************************************************************
//Callback function on advertisement 
//*********************************************************************************
void RFduinoBLE_onAdvertisement(bool start)
{
  Serial.println("RFduino is doing BLE advertising ...");
}


//*********************************************************************************
//Callback function on connect
//*********************************************************************************
void RFduinoBLE_onConnect()
{
  Serial.println("RFduino BLE connection successful");
}


//*********************************************************************************
//Callback function on disconnect
//*********************************************************************************
void RFduinoBLE_onDisconnect()
{
  Serial.println("RFduino BLE disconnected");
  digitalWrite(TENS_StimulPin, LOW);
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(LEDs[i], LOW);
    delay (500);
  }
}


//*********************************************************************************
// returns the dBm signal strength indicated by the receiver after connection (-0dBm to -127dBm)
//*********************************************************************************
void RFduinoBLE_onRSSI(int rssi)
{
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
       digitalWrite(LEDs[3], HIGH);
    } 
    else{
      MAX = highEMG; 
      digitalWrite(LEDs[4], HIGH);
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
  
  uint8_t MyoSensor1[10];
  uint8_t MyoSensor2[10];
  uint8_t MyoSensor3[10];
  uint8_t MyoSensor4[10];
  
  //Take 10 EMG readings in 0.001 seconds
  for(int index=0; index<10; index++){
    MyoSensor1[index] = data[0] * multiplier;
    MyoSensor2[index] = data[1] * multiplier;
    MyoSensor3[index] = data[2] * multiplier;
    MyoSensor4[index] = data[3] * multiplier;
    //delay(1);
  }
  
  //Take average of the 10 readings
  for(int i = 0; i < 10; i++){
    avgSensor1 +=  MyoSensor1[i];
    avgSensor2 +=  MyoSensor2[i];
    avgSensor3 +=  MyoSensor3[i];
    avgSensor4 +=  MyoSensor4[i];
  }
  AverageEMG = (avgSensor1 + avgSensor2 + avgSensor3 + avgSensor4)/16;
  Serial.print(AverageEMG);
  Serial.print("\t");
 
  finalReading = constrain(AverageEMG, 0, MAX);                           //Constrains AverageEMG to MAX
  level = map(finalReading, 0, MAX,0, MAX_LED);                           //maps MAX_LED to AverageEMG

  digitalWrite(TENS_StimulPin, LOW);                                      //TENS device deactivated
  
  for(int thisLED = 0; thisLED < MAX_LED; thisLED++){                     //write all LEDs low and stim pin low
    digitalWrite(LEDs[thisLED], LOW);
    digitalWrite(TENS_StimulPin, LOW); 
  }
  Serial.println(level);

  // Reset variables
  avgSensor1 = 0;
  avgSensor2 = 0;
  avgSensor3 = 0;
  avgSensor4 = 0;
  AverageEMG = 0;

  for(int thisLed = 0; thisLed < level; thisLed++){   //Turns on the LEDs  
   if(level > thisLed)
      digitalWrite(LEDs[thisLed],HIGH); 
    else 
      digitalWrite(LEDs[thisLed],LOW); 
    
    if(thisLed >= ThresholdVAL){                    //Turns the TENS on as a function of which LED is lit
      digitalWrite(TENS_StimulPin, HIGH);
      delay(1);
    }
    else
      digitalWrite(TENS_StimulPin, LOW);
  } 
  
  for (int i=0; i<4; i++){
     data[i]= 0; 
  }

  Serial.flush();

}

