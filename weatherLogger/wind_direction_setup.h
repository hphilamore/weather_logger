/*
 *  |----- Vvane (e.g. 3.3V) 
 *  |
 *  | 
 *  |
 *  |----- vane 1 and Pin 9
 *  
 *  
 *  |----- vane 4 and Pin A1
 *  | 
 *  | Rvane = 10K
 *  |
 *  |----- GND
 */

#define Vvane 3.3    // the supply voltage of the wind vane
#define Rvane 10000  // the fixed resister in the voltage divider circuit 
#define vane_pin A1  // the pin to read the sensor voltage on

// 0 points north
float  vane_angle[16]      = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5};
float  vane_resistance[16] = {33000, 6570, 8200, 891, 1000, 688, 2200, 1410, 3900, 3140, 16000, 14120, 120000, 42120, 64900, 21880};
//float vane_voltage[16]  = {2.53, 1.30, 1.48, 0.26, 0.3, 0.21, 0.59, 0.40, 0.92, 0.78, 2.03, 1.93, 3.04, 2.66, 2.85, 2.264}
float vane_voltage[16];
float voltage_diff[16];   
float windDirection;
float minimum;




