#include <RFduinoBLE.h>
#define RED_LED_PIN   2
#define GREEN_LED_PIN 3
#define BLUE_LED_PIN  4

void setup()
{
  // Set pins as outputs.
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Enable serial debug, type cntrl-M at runtime.
  override_uart_limit = true;
  Serial.begin(115200);
  Serial.println("RFduino example started");
  Serial.println("Serial rate set to 9600 baud");

  // All LEDs are initially turned off
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  // Indicate RGB LED is operational to user.
  digitalWrite(RED_LED_PIN, HIGH);    // red
  delay (500);
  digitalWrite(GREEN_LED_PIN, HIGH);  // green
  delay (500);  
  digitalWrite(BLUE_LED_PIN, HIGH);   // blue
  delay (500);
  digitalWrite(RED_LED_PIN, LOW);     // lights out
  delay (300);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay (300);
  digitalWrite(BLUE_LED_PIN, LOW);
  delay (300);


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
  //RFduinoBLE.send(1);
 
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
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
}

// returns the dBm signal strength indicated by the receiver after connection (-0dBm to -127dBm)
void RFduinoBLE_onRSSI(int rssi)
{
}
void RFduinoBLE_onReceive(char *data, int len)
{
  // If the first byte is 0x01 / on / true
  Serial.println("Received data over BLE");
  /*for (;;){
    
    if (data){
      Serial.println(data++); 
    }
    else{ 
      break;
    }
  }*/

  
  for (int i=0; i<len; i++){
    Serial.println(data); 
  }
  
  //if (data[0])
  if (data[0])
  {
    digitalWrite(BLUE_LED_PIN, HIGH);
    Serial.println("Turn RFduino Blue LED On");
  }
  else
  {
    digitalWrite(BLUE_LED_PIN, LOW);
    Serial.println("Turn RFduino Blue LED Off");
  }

  uint8_t r = data[0];
  uint8_t g = data[1];
  analogWrite(RED_LED_PIN, r);
  analogWrite(GREEN_LED_PIN, g);
  Serial.print("First byte");
  Serial.print("\t");
  Serial.println(r);
}

