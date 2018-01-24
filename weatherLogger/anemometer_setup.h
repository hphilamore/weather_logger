/*
 *  |----- Vs (e.g. 3.3V) 
 *  |
 *  | 10k
 *  |
 *  |----- anemometer 2 and Pin 9
 *  
 *  
 *  |----- anemometer 1
 *  | 
 *  | 300
 *  |
 *  |----- GND
 */
 
#define anemometer_measure_period 1000
#define anemometer_pin 9

int anemometer_count = 0;
//unsigned long T_old = millis();
float windspeed;



