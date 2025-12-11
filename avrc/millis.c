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
void millis_init(void)
{
	TCCR0A = (1<<WGM01);			//CTC
	TCCR0B = (1<<CS01)|(1<<CS00);	//prescaler 64
	OCR0A = 249;
	TIMSK0 |= (1<<OCIE0A);			//CTC interrupt
}
unsigned long micros(void)
{
    unsigned long m;
    uint8_t t;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)//this is here acts like a cli() to disable interupts just to read the values for timer and tcnt0 so its not distorted
    {
        m = timer; //timer is global value incremented by the isr
        t = TCNT0;//reads current timer0 value
    }
    
    return ((m * 1000) + (t * 4));//m*1000 converts miliseconds to microseconds. Multiplied by 4 because every timer0 tick is 4 micsec.
}
