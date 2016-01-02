/*RFduinoRecieve_Demo.ino by Boniface
 *
 *This is a demo code to show RFduino communication with MYO,
 *it writes the signals recieved from Myo to the LEDs as analog values.
 *
 *Note: if the RFduino is plugged to the USB shield, GPIO 0 and GPIO 1 will be  high because they
 *are pulled high by the FTDI USB to UART. Using an alternative power source(e.g bettery shield) 
 * will eliminate this problem. Also, calling Serial.begin will use GPIO 1.
 *
 *********************************     Version_1     ********************************************
 */

#include <RFduinoBLE.h>

#define MAX_LED 7

int LEDs[] = {0,1,2,3,4,5,6};

void setup()
{
  // Set pins as outputs.
  for(int i=0; i<MAX_LED; i++){
    pinMode(LEDs[i], OUTPUT);
  }

  // Enable serial debug, type cntrl-M at runtime.
  override_uart_limit = true;
  Serial.begin(115200);
  Serial.println("RFduino example started");
  Serial.println("Serial rate set to 115200 baud");

  // All LEDs are initially turned off
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(LEDs[i], LOW);
  }

  // Indicate that LEDs are operational to user.
  for(int i=0; i<MAX_LED; i++){
    digitalWrite(LEDs[i], HIGH);
    delay (500);
  }
  for(int i=0; i<MAX_LED; i++){
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

  uint8_t a,b,c,d,e,f,g,h; 
  a = data[0]; Serial.print(a); Serial.print("\t");
  b = data[1]; Serial.print(b); Serial.print("\t");
  c = data[2]; Serial.print(c); Serial.print("\t");
  d = data[3]; Serial.print(d); Serial.print("\t");
  e = data[4]; Serial.print(e); Serial.print("\t");
  f = data[5]; Serial.print(f); Serial.print("\t");
  g = data[6]; Serial.println(g);

  analogWrite(LEDs[0],a);
  analogWrite(LEDs[1],b);
  analogWrite(LEDs[2],c);
  analogWrite(LEDs[3],d);
  analogWrite(LEDs[4],e);
  analogWrite(LEDs[5],f);
  analogWrite(LEDs[6],g);

  Serial.flush();
}
 
  


