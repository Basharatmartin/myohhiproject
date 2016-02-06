
---VERSIONS---
	- RFduino_Receive_V1.ino
	- RFduino_Receive_V2.ino
	- RFduino_Receive_V3.ino
 
 
---GENERAL NOTE---
 If the RFduino is plugged to the USB shield, GPIO 0 and GPIO 1 will be  high because they
 are pulled high by the FTDI USB to UART. Using an alternative power source(e.g bettery shield) 
 will eliminate this problem. Also, calling Serial.begin will use GPIO 1.
 
 
---RFduino_Receive_V1.ino---
	* This is a demo code to show RFduino communication with MYO.
	* It writes the signals recieved from Myo to the LEDs as analog values.
	* Prints values received from MYO to the serial terminal.
 
 
 ---RFduino_Receive_V1.ino---
	*  Realizes only one movement of the hand (Arm actuation)
 
 
 ---RFduino_Receive_V1.ino---
	* Realizes three different movements of the hand, i.e,
		. hand left, 
		. hand right and 
		. whole arm movement