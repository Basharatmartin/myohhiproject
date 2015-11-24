#include <RFduinoBLE.h>
#define Led1  3
#define Led2  4
#define Led3  5
#define Led3  6
#define highEMG 300
#define lowEMG 100

int LEDs[] = {3,4,5,6};
int SwitchThresholdState = 0;
int SwitchState = 0;
int MAX;
int SwitchStatePin = 0;
int SwitchThresholdPin = 1;

void setup()
{
  // Set pins as outputs.
  for(int i=0; i<4; i++){
    pinMode(LEDs[i], OUTPUT);
  }
  pinMode(SwitchStatePin,INPUT);
  pinMode(SwitchThresholdPin,INPUT);

  // Enable serial debug, type cntrl-M at runtime.
  override_uart_limit = true;
  Serial.begin(115200);
  Serial.println("RFduino example started");
  Serial.println("Serial rate set to 9600 baud");

  // All LEDs are initially turned off
  for(int i=0; i<4; i++){
    digitalWrite(LEDs[i], LOW);
  }

  // Indicate that LEDs are operational to user.
  for(int i=0; i<4; i++){
    digitalWrite(LEDs[i], HIGH);
    delay (500);
  }
  for(int i=0; i<4; i++){
    digitalWrite(LEDs[i], LOW);
    delay (500);
  }


  //Configuration for RFduino  
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

  MAX = highEMG;
}

void loop()
{
  // switch to lower power mode
  RFduino_ULPDelay(INFINITE);  

  // to send one char
  // RFduinoBLE.send((char)temp);
 
  // to send multiple chars
  // RFduinBLE.send(&data, len);
} 


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
 for(int i=0; i<4; i++){
    digitalWrite(LEDs[i], LOW);
    delay (500);
  }
}

// returns the dBm signal strength indicated by the receiver after connection (-0dBm to -127dBm)
void RFduinoBLE_onRSSI(int rssi)
{
}
void RFduinoBLE_onReceive(char *data, int len)
{ 
  Serial.println("Received data over BLE");
/*
SwitchThresholdState = digitalRead(SwitchThresholdPin);
  Serial.print("SwitchThresholdState: "); Serial.println(SwitchThresholdState);
  if (SwitchThresholdState == HIGH) {
    if(MAX == highEMG){ 
      Serial.print("High EMG: "); Serial.println(MAX); 
      MAX = lowEMG;         
    } 
    else{
      Serial.print("LOW EMG: "); Serial.println(MAX);
      MAX = highEMG;          
    } 
  }
  while (SwitchThresholdState == HIGH) { // This will pause the program while the person is touching the threshold button, 
    SwitchThresholdState = digitalRead(SwitchThresholdPin);         
    delay(1000); 
  }// so it doesn't flip back and forth while button is pushed
   

  SwitchState = digitalRead(SwitchStatePin);
  Serial.print("SwitchState: "); Serial.println(SwitchState);
  while (SwitchState == HIGH) { // This will pause the program while the person is touching TENS test button
      SwitchState = digitalRead(SwitchStatePin);  
      Serial.println("...wait, setting up TENS...");
      delay(1000); 
  } 
*/


  //uint8_t *arr = (uint8_t *)data;
  //for (int i=0; i<len; i++){
    //Serial.println(arr[i]); 
  //}
  

  int a,b,c,d,e,f,g,h; 
  a = data[0]; Serial.print(a); Serial.print("\t");
  b = data[1]; Serial.print(b); Serial.print("\t");
  c = data[2]; Serial.print(c); Serial.print("\t");
  d = data[3]; Serial.print(d); Serial.print("\t");
  e = data[4]; Serial.print(e); Serial.print("\t");
  f = data[5]; Serial.print(f); Serial.print("\t");
  g = data[6]; Serial.print(g); Serial.print("\t");
  h = data[7]; Serial.println(h); 
  analogWrite(3,a);
  analogWrite(4,b);
  analogWrite(5,c);
  analogWrite(6,d);

  Serial.flush();
}
 
  


