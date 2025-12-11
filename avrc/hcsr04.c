#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "pwm.h"

#define PRESCALER 64
void hcsr04_init(void)
{
	//CLOCK1 freq = 250kHZ
	init_fastpwm_icr1(PRESCALER);
	set_top_in_icr1(pwm_ICRn_val(F_CPU, 10, PRESCALER));
	set_duty_ocr1A(3);	//16uS

	//this will setup PCINT1, TODO init PCINT0 and PCINT2 and make a separated fn
	PCICR = (1<<PCIE1);
	PCMSK1 = (1<<PCINT13);
	//use EICRA reg to execute ISR block on rising/falling edge only?
	EICRA = (1<<ISC10);	//Any logical change on INT1 generates an interrupt request.
}
