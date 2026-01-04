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

	//this will setup PCINT1, TODO init PCINT0 and PCINT2 and make a separated fn
	PCICR = (1<<PCIE2)|(1<<PCIE1)|(1<<PCIE0);

	//PD5 
	PCMSK2 = (1<<PCINT21);
	//PB0
	PCMSK1 = (1<<PCINT8);
	//PC5
	PCMSK0 = (1<<PCINT5);

	//Any logical change on INT1 and INT0 generates an interrupt request.
	EICRA = (1<<ISC10)|(1<<ISC01);
}

