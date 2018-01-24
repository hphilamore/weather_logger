void rotations(){
  anemometer_count +=1; 
}


void wind_speed(){
//  if ((millis() - T_start) > anemometer_measure_period){ 
////    Serial.print("calculating wind speed");
//    calculate_wind_speed();
//    }
Serial.println(timer);
T_start = millis();
}


void calculate_wind_speed(){
//  detachInterrupt(0);
//  unsigned long T = millis();
//  Serial.println(T-T_old);
//  Serial.println(anemometer_count);
//  float frequency = 1000 * anemometer_count / (T - T_old);
//  Serial.println(frequency);
//  windspeed = frequency * 0.66; 
//  T_old = millis();
//  anemometer_count = 0;

//  Serial.println(T_start);

//    float period = float(millis()-T_start);
//    Serial.println(millis());
//    Serial.println(T_start);
//    Serial.println(period);
//    int count = anemometer_count;
//    Serial.println(anemometer_count);
//    //float frequency = 1000*float(count/period); 
//    float frequency = float(count/period); 
//    Serial.println(frequency);
//    windspeed = frequency * 0.66; 
//    Serial.println(windspeed);
//    T_start = millis();
//    anemometer_count = 0;



}

