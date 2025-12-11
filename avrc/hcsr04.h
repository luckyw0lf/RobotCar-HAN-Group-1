#ifndef HCSR04_H_ 
#define HCSR04_H_ 
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "pwm.h"
//extern volatile uint16_t hcsr04_distance_cm; 
 
volatile unsigned int hcsr04_distance_cm = 0;
volatile signed char edge = 1;
volatile unsigned long timer_start = 0;	//make them global?
volatile unsigned long timer_stop = 0;
ISR(PCINT1_vect)
{
		if (1 == edge )//rising edge
		{
			timer_start = TCNT1; //on rising edge
		}
		else	//falling edge
		{
			timer_stop = TCNT1;
			hcsr04_distance_cm = (((timer_stop - timer_start)*4)/58);
		}
		edge *= -1;
}
void hcsr04_init(void); 
 
#endif /* HCSR04_H_ */
