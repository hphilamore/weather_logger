
void wind_direction(){
  float reading  = analogRead(vane_pin);      // voltage on voltage divider pin read as binary value (range 0 to 1023)   
  float voltage = reading*(Vvane/1023.0);     // binary value converted to voltage


  // calculate the theoretical voltage output at each angle, based on the supply voltage and voltage divider circuit
  for(int i=0; i <= 17; i++){
    vane_voltage[i] = Vvane * Rvane / (Rvane + vane_resistance[i]); 
  }


  for (int i=0; i <= 17; i++){
    voltage_diff[i] = abs(vane_voltage[i] - voltage);
  }


  minimum  = voltage_diff[0];
  windDirection = vane_angle[0];

  
  for (int i=0; i <= 17; i++){
      if (minimum > voltage_diff[i]){
          minimum  = voltage_diff[i];
          windDirection = vane_angle[i];
      }      
  }

}

