#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "pwm.h"

#define PRESCALER 64
void init_hcsr04(void)
{
	//CLOCK1 freq = 250kHZ
	init_fastpwm_icr1(PRESCALER);
	set_top_in_icr1(pwm_ICRn_val(F_CPU, 10, PRESCALER));
	set_duty_ocr1A(3);	//16uS

	//Enabling interrupts
	PCICR = (1<<PCIE2)|(1<<PCIE1)|(1<<PCIE0);

	//Pin selection
	PCMSK2 = (1<<PCINT21);	//pd5
	PCMSK1 = (1<<PCINT13);	//pc5
	PCMSK0 = (1<<PCINT5);	//pb5

	//Any logical change on INT1 and INT0 generates an interrupt request.
	EICRA = (1<<ISC10)|(1<<ISC01);
}

extern volatile signed char edge_PCINT2;
extern volatile signed char edge_PCINT1;
extern volatile signed char edge_PCINT0;
extern volatile unsigned long timer_start_PCINT2;
extern volatile unsigned long timer_stop_PCINT2;
extern volatile unsigned long timer_start_PCINT1;
extern volatile unsigned long timer_stop_PCINT1;
extern volatile unsigned long timer_start_PCINT0;
extern volatile unsigned long timer_stop_PCINT0;

void init_hcsr04_edges()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		edge_PCINT2 = 1;
		edge_PCINT1 = 1;
		edge_PCINT0 = 1;

		timer_start_PCINT2 = 0;
		timer_stop_PCINT2 = 0;
		timer_start_PCINT1 = 0;
		timer_stop_PCINT1 = 0;
		timer_start_PCINT0 = 0;
		timer_stop_PCINT0 = 0;
	}
}
