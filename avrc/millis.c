//GPL-3.0-only
#define __AVR_ATmega328P__

#define MILLIS_TIMER0
//#define MILLIS_TIMER1
//#define MILLIS_TIMER2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

volatile unsigned long timer = 0;
volatile unsigned long ms = 0;

#ifdef MILLIS_TIMER0
	ISR(TIMER0_COMPA_vect)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			timer++;
	}
#endif //MILLIS_TIMER0

#ifdef MILLIS_TIMER1
	ISR(TIMER1_COMPA_vect)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			timer++;
	}
#endif //MILLIS_TIMER1

#ifdef MILLIS_TIMER2
	ISR(TIMER2_COMPA_vect)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			timer++;
	}
#endif //MILLIS_TIMER2

unsigned long millis(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		ms = timer;
	return (ms);
}
void init_millis_timer0(void)
{
	TCCR0A = (1<<WGM01);			//CTC
	TCCR0B = (1<<CS01)|(1<<CS00);	//prescaler 64
	OCR0A = 249;
	TIMSK0 |= (1<<OCIE0A);			//CTC interrupt
}
void init_millis_timer1(void)
{
	// ./utils/timer-ICRn-helper.sh "(10 ^ -3)"
	//prescaler    1	ICRn = 15999	16bit TIMER ok
	//prescaler    8	ICRn =  1999	16bit TIMER ok

	TCCR1B = (1<<WGM12)|(1<<CS11);	//prescaler 8, CTC with top in OCR1A
	OCR1A = 1999;
	TIMSK1 |= (1<<OCIE1A);			//CTC interrupt
}
void init_millis_timer2(void)
{
	TCCR2A = (1<<WGM21);		//CTC
	TCCR2B = (1<<CS22);			//prescaler 64
	OCR2A = 249;
	TIMSK2 |= (1<<OCIE2A);		//CTC interrupt

}
