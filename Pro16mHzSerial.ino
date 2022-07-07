/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

SERIAL.print((char)STK_INSYNC);
 
spi_transaction(0xAC, 0x53, 0x00, 0x00);


SERIAL.print((char)STK_NOSYNC);

 #define RESET     10 // Use pin 10 to reset the target rather than SS
  #define LED_HB    9
     
#define STK_FAILED  0x11
#define STK_UNKNOWN 0x12
#define STK_INSYNC  0x14
#define STK_NOSYNC  0x15
#define CRC_EOP     0x20 //ok it is a space...

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include "Arduino.h"
#include <SoftwareSerial.h>

#undef SERIAL
#ifdef SERIAL_PORT_USBVIRTUAL
  #define SERIAL SERIAL_PORT_USBVIRTUAL
#else
  #define SERIAL Serial
#endif

#define BAUDRATE  2400
//#define BAUDRATE  19200
// #define BAUDRATE 115200

#define STK_OK      0x10    //DLE
#define STx_str      0x02    //STX
#define cR_str      0x13    //cR
#define LF_str      0x10    //LF

#define LED_PMODE 13  //17
#define LED_SCKpb5   5

//  Serial.begin(9600); //This pipes to the serial monitor
 // Serial.println("Initialize Serial Monitor");

  //Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
  //Serial1.println("Initialize Serial Hardware UART Pins");
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  
pinMode(LED_PMODE, OUTPUT);
pinMode(LED_SCKpb5, OUTPUT);

prog_lamp(LOW);
delayMicroseconds(1000);        
prog_lamp(HIGH);
delayMicroseconds(1000);

  // Open serial communications and wait for port to open:
  SERIAL.begin(BAUDRATE);
//  Serial.begin(9600);
  //while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  //}


  Serial.println("Arduino Pro 5 V. 16 mHz!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(2400);
  mySerial.println("Pro16mHzSerial.ino");
}

void prog_lamp(int state) {
      digitalWrite(LED_PMODE, state);
      digitalWrite(LED_SCKpb5, state);
  }

void loop() { // run over and over
  int ISPError = 0;
  
  //if (mySerial.available()) {
  SERIAL.print((char) STx_str);
  //  Serial.write(2);
  
  Serial.write("  99  12340 kg ");
  Serial.write(13);
  Serial.write(10);
  
    SERIAL.print((char) STK_OK);
  
    //Serial.write(mySerial.read());
  //}
  //if (Serial.available()) {
    
 //   mySerial.write(Serial.read());
 mySerial.write("mySerial");
prog_lamp(LOW);
delay(200);
prog_lamp(HIGH);
delay(200);
ISPError++;
 Serial.write(ISPError);

//STK_OK++;
  //}
}
