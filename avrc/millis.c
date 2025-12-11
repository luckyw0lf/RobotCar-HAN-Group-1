//GPL-3.0-only
#define __AVR_ATmega328P__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>


extern volatile unsigned long timer;

volatile unsigned long ms = 0;
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
	TIMSK0 = (1<<OCIE0A);			//CTC interrupt
}
void init_millis_timer1(void)
{
	// ./utils/timer-ICRn-helper.sh "(10 ^ -3)"
	//prescaler    1	ICRn = 15999	16bit TIMER ok
	//prescaler    8	ICRn =  1999	16bit TIMER ok

	TCCR1B = (1<<WGM12)|(1<<CS11);	//prescaler 8, CTC with top in OCR1A
	OCR1A = 1999;
	TIMSK1 = (1<<OCIE1A);			//CTC interrupt
}
void init_millis_timer2(void)
{
	TCCR2A = (1<<WGM21);		//CTC
	TCCR2B = (1<<CS22);			//prescaler 64
	OCR2A = 249;
	TIMSK2 = (1<<OCIE2A);		//CTC interrupt

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
