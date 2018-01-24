void column_headings_to_SD(){
 /*  
  *  Parameters not being loggedshould be commented out
  */
  
  // open the file to write data
  logfile = SD.open(filename, FILE_WRITE);
  
  // if there is no SD card, print error message
  if( ! logfile ) {
    Serial.print("Couldnt create/open file: ");
    Serial.println(filename);
    errorLED(3);
  }
  
  logfile.print("Date"); logfile.print("\t"); logfile.print("Time"); 
  logfile.print("\t");
  if (ECHO_TO_SERIAL){
    Serial.print("Date"); Serial.print("\t"); Serial.print("Time"); 
    Serial.print("\t");
  }

  // UV index
  logfile.print("UV_index"); 
  logfile.print("\t");
  if (ECHO_TO_SERIAL){  
    Serial.print("UV_index");
    Serial.print("\t");
  }
 
  // windspeed
  logfile.print("windspeed_(m/s)"); 
  logfile.print("\t");
  if (ECHO_TO_SERIAL){  
    Serial.print("windspeed_(m/s)");
    Serial.print("\t");
  }

  // windDirection
  logfile.print("wind_angle(deg_from_north)"); 
  logfile.print("\t");
  if (ECHO_TO_SERIAL){  
    Serial.print("wind_angle(deg_from_north)");
    Serial.print("\t");
  }

  logfile.print("\n");
  if (ECHO_TO_SERIAL){  
    Serial.print("\n");
  }

  // close the file ensuring that written data is physically saved to the SD card
  logfile.close();
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


  // write uv index to file on SD card (and serial monitor)
  logfile.print(UVindex); 
  logfile.print("\t");
  if (ECHO_TO_SERIAL){
    Serial.print(UVindex);
    Serial.print("\t");
  }


  // write windspeed to file on SD card (and serial monitor)
  logfile.print(windspeed); 
  logfile.print("\t");
  if (ECHO_TO_SERIAL){
    Serial.print(windspeed);
    Serial.print("\t");
  }

  // write windspeed to file on SD card (and serial monitor)
  logfile.print(windDirection); 
  logfile.print("\t");
  if (ECHO_TO_SERIAL){
    Serial.print(windDirection);
    Serial.print("\t");
  }
  
  logfile.print("\n");
  if (ECHO_TO_SERIAL){  
    Serial.print("\n");
  }


  // close the file ensuring that written data is physically saved to the SD card
  logfile.close();

}

