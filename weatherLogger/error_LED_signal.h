void errorLED(uint8_t errno) {
/* 
 *  The error number is shown by the number of red LED flashes (followed by pause) 
 */
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
