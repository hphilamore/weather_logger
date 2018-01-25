#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTCZero.h>
#include "UV_lightmeter_setup.h"
#include "anemometer_setup.h"

#define cardSelect 4            // pin used for SD card
#define LOG_INTERVAL 1000       // mills between entries
#define ECHO_TO_SERIAL true    // echo data to serial port
#define redLED 13
#define greenLED 8
#include "error_LED_signal.h"


char filename[15];            // create text array with desired number of characters
File logfile;                 // create logging file object
RTCZero rtc;                  // create real time clock object

// RTC time and date setup
// Set to true and set clock a few seconds in the future.
// Set to false and re-upload the program (if the board remains powered, the RTC will hold the date/time)
int set_RTC_date_time = 1;
int D = 23, M = 1, Y = 18;
int h = 16, m = 42, s = 0; 


void setup() {
  // 115200 to read the GPS fast enough and echo without dropping chars
  Serial.begin(115200);
  
  // Start the RTC
  Wire.begin();  
  rtc.begin();

  // set the date and time
  if (set_RTC_date_time){
    rtc.setTime(h, m, s);  
    rtc.setDate(D, M, Y);  
  }    
  
  // on baord LED pins
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect)) {
    Serial.println("Card init. failed!");
    errorLED(2);
  }
  
  // comment out if not using UV sensor
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }
  
  // initialise the variable filename with a string
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
  
  column_headings_to_SD();

  // comment out if ot using anemometer
  pinMode(9, INPUT);
  attachInterrupt(digitalPinToInterrupt(9), rotations, RISING);
}


uint8_t i=0;

void loop() {

  readUVindex();

  wind_speed();
  
  
  // LED on to show device is on
  digitalWrite(greenLED, HIGH);

  // save data to SD card (and print to serial) 
  save_to_SD();

  // LED off to show readings have bee taken
  digitalWrite(greenLED, LOW);

  // delay between readings
  delay(LOG_INTERVAL);

  //Serial.println(anemometer_count);
 } 


 void save_to_SD(){
  /* 
   *  Saves data to SD card (and optionally prints to serial)
   *  Parameters not being loggedshould be commented out
   */
  // open the file to write data
  logfile = SD.open(filename, FILE_WRITE);
  
  // if there is no SD card, print error message
  if( ! logfile ) {
    Serial.print("Couldnt create/open file: ");
    Serial.println(filename);
  }

   
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


//  // write uv index to file on SD card (and serial monitor)
//  logfile.print(UVindex); 
//  logfile.print("\t");
//  if (ECHO_TO_SERIAL){
//    Serial.print(UVindex);
//    Serial.print("\t");
//  }


//  // write windspeed to file on SD card (and serial monitor)
//  logfile.print(windspeed); 
//  logfile.print("\t");
//  if (ECHO_TO_SERIAL){
//    Serial.print(windspeed);
//    Serial.print("\t");
//  }
  
//  logfile.print("\n");
//  if (ECHO_TO_SERIAL){  
//    Serial.print("\n");
//  }


  // close the file ensuring that written data is physically saved to the SD card
  logfile.close();

}


//void rpm_fun()
// {
//   //Each rotation, this interrupt function is run twice, so take that into consideration for 
//   //calculating RPM
//   //Update count
//   //count++;  // use if count is byte
//   count +=1;
//      
// }
