//GPL-3.0-only
#ifndef MILLIS_H_
 #define MILLIS_H_

#include <avr/interrupt.h>
#include <util/atomic.h>

//will be declared as extern in millis.c
volatile unsigned long timer = 0;

//MILLIS_TIMER macros will be expanded to an actual ISR vector
//to select a clock for millis(), #define MILLIS_TIMER TIMERn_COMPA_vect
//BEFORE including millis.h
ISR(TIMER2_COMPA_vect)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		timer++;
}

//select timer to init
void init_millis_timer0(void);
void init_millis_timer1(void);
void init_millis_timer2(void);

//returns current ms value
unsigned long millis(void);
unsigned long micros(void);

#endif // MILLIS_H_
