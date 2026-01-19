//GPL-3.0-only
// #define MILLIS_TIMER TIMER2_COMPA_vect
#include "../avrc/millis.h"
#include <avr/io.h>

#define DEBOUNCE_DELAY 50

extern volatile char mode;                 

unsigned long oldTime;
unsigned long deltaTime;
unsigned long lastDebounceTime = 0;
signed char lastButtonState = 1; 
signed char reset = 1; 

/**
 * WARNING! this initializes milis timer 2 for the button!
 */
void initButton(){
  init_millis_timer2();
  sei();
}

void checkButton() {
  int reading = (PINB & (1 << PINB7));

  // Debounce logic
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }	

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // Button is stable
    if (reset == 0) {
        reset = 1;
        if (mode > 1) 
            mode = 0;
        else 
            mode++;
    }
  } else {
    reset = 0;
  }
  
  lastButtonState = reading;
}