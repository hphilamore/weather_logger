#include <SPI.h>
#include <SD.h>
#include <Wire.h>

// Set the pins used
#define cardSelect 4

// create text array with desired number of characters
char filename[15];

File logfile;

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
      for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
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
  pinMode(13, OUTPUT);

  
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


  // on baord LED pins
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  
  // LED on
  digitalWrite(8, HIGH);


  // write reading to file on SD card and serial monitor
  logfile.print("A0 = "); logfile.println(analogRead(0));
  Serial.print("A0 = "); Serial.println(analogRead(0));


  // LED off
  digitalWrite(8, LOW);


  // 100 ms delay between readings
  delay(1000);


  // close the file ensuring that written data is physically saved to the SD card
  logfile.close();
}
