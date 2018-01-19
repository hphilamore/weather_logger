#include <SPI.h>
#include <SD.h>
#include <Wire.h>

// Set the pins used
#define cardSelect 4

// A simple data logger for the Arduino analog pins
#define LOG_INTERVAL  1000 // mills between entries
#define ECHO_TO_SERIAL   1 // echo data to serial port
#define WAIT_TO_START    0 // Wait for serial input in setup()

// the digital pins that connect to the LEDs
#define redLED 13
#define greenLED 8

// The analog pins that connect to the sensors
#define photocellPin 0           // analog 0
#define tempPin 1                // analog 1


// create text array with desired number of characters
char filename[15];

File logfile;

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
      for (i=0; i<errno; i++) {
      digitalWrite(redLED, HIGH);
      delay(100);
      digitalWrite(redLED, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}



void setup() {
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("\r\nAnalog logger test");
  
    // on baord LED pins
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  
  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }

    
  // assign the desired file name to the variable filename 
  strcpy(filename, "ANALOG00.TXT");


  // loop through 100 possible filenames...
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = '0' + i/10;
    filename[7] = '0' + i%10;

    
    // ...stop when an unused filename is reached
    if (! SD.exists(filename)) {
      Serial.print("Writing to ");
      Serial.println(filename);
      break;
    }
  }
}


uint8_t i=0;
void loop() {

  // open the file to write data
  logfile = SD.open(filename, FILE_WRITE);

  
  // if there is no SD card, print error message
  if( ! logfile ) {
    Serial.print("Couldnt create/open file: ");
    Serial.println(filename);
    error(3);
  }




  
  // LED on
  digitalWrite(greenLED, HIGH);


  // write reading to file on SD card and serial monitor
  logfile.print("A0 = "); logfile.println(analogRead(photocellPin));
  Serial.print("A0 = "); Serial.println(analogRead(photocellPin));


  // LED off
  digitalWrite(greenLED, LOW);


  // 100 ms delay between readings
  delay(1000);


  // close the file ensuring that written data is physically saved to the SD card
  logfile.close();
}
