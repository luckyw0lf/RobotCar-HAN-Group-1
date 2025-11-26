//GPL-3.0-only
#define __AVR_ATmega328P__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

volatile long timer = 0;
volatile long ms = 0;

ISR(TIMER0_COMPA_vect)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		timer++;
}
unsigned long millis(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		ms = timer;
	return (ms);
}
void millis_init_timer0(void)
{
	TCCR0A = (1<<WGM01);			//CTC
	TCCR0B = (1<<CS01)|(1<<CS00);	//prescaler 64
	OCR0A = 249;
	TIMSK0 |= (1<<OCIE0A);			//CTC interrupt
}
