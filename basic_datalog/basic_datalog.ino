#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTCZero.h>
#include <Adafruit_SI1145.h>

// Set the pins used
#define cardSelect 4

// A simple data logger for the Arduino analog pins
#define LOG_INTERVAL  1000 // mills between entries
#define ECHO_TO_SERIAL   1 // echo data to serial port

// the digital pins that connect to the LEDs
#define redLED 13
#define greenLED 8

// The analog pins that connect to the sensors
#define photocellPin 0           // analog 0
#define tempPin 1                // analog 1


// create text array with desired number of characters
char filename[15];


// create logging file object
File logfile;

// create real time clock object
RTCZero rtc;    // Create RTC object

// create uv object
Adafruit_SI1145 uv = Adafruit_SI1145();


// blinks out the same number of red LED flashes as the error number, then pauses
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
      delay(500);
    }
  }
}



void setup() {

  // Start the RTC
  Wire.begin();  
  rtc.begin();

  // Start the UV sensor
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }


  // Type in a time a few seconds in the future and hit upload to set it
  // Then comment this line out and re-upload the program (if the board remains powered, the RTC will hold the date/time)
//  // Set the time (H, M, S)
//    rtc.setTime(20, 14, 0);  
//  // Set the date (D, M, Y) 
//    rtc.setDate(19, 1, 18);    
 
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
    if (! SD.exists(filename)){
      break;
    }    
  }
  
  Serial.print("Writing to ");
  Serial.println(filename);

  // Column headings for output files
  logfile = SD.open(filename, FILE_WRITE);
  logfile.print("Date");
  logfile.print("\t");    
  logfile.print("Time");
  logfile.print("\t");
  logfile.print("UV_index");
  logfile.println("\t");
  logfile.close();

  if (ECHO_TO_SERIAL){
    Serial.print("Date");
    Serial.print("\t");    
    Serial.print("Time");
    Serial.print("\t");
    Serial.print("UV_index");
    Serial.println("\t");
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


  // write timestamp to file on SD card (and serial monitor)
  logfile.print(rtc.getDay()); logfile.print("/"); logfile.print(rtc.getMonth()); logfile.print("/"); logfile.print(rtc.getYear());
  logfile.print("\t");    
  logfile.print(rtc.getHours()); logfile.print(":"); logfile.print(rtc.getMinutes()); logfile.print(":"); logfile.print(rtc.getSeconds());
  logfile.print("\t");

  if (ECHO_TO_SERIAL){
    Serial.print(rtc.getDay()); Serial.print("/"); Serial.print(rtc.getMonth()); Serial.print("/"); Serial.print(rtc.getYear());
    Serial.print("\t");
    Serial.print(rtc.getHours()); Serial.print(":"); Serial.print(rtc.getMinutes()); Serial.print(":"); Serial.print(rtc.getSeconds());
    Serial.print("\t");
  }


  // calculate uv index 
  float UVindex = uv.readUV();
  UVindex /= 100.0; 
  
  // write uv index to file on SD card (and serial monitor)
  logfile.println(UVindex); 
  if (ECHO_TO_SERIAL){
    Serial.println(UVindex);
  }

  // LED off
  digitalWrite(greenLED, LOW);

  // close the file ensuring that written data is physically saved to the SD card
  logfile.close();

  // delay between readings
  delay(LOG_INTERVAL);
  
}
