void rotations(){
  anemometer_count +=1; 
}


void wind_speed(){
  if ((millis() - T_old) > anemometer_measure_period){ 
    calculate_wind_speed();
    }
}


void calculate_wind_speed(){
  detachInterrupt(0);
  unsigned long T = millis();
  float frequency = 1000 * anemometer_count / (T - T_old);
  windspeed = frequency * 0.66; 
  T_old = millis();
  anemometer_count = 0;
}

