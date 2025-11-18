//GPL-3.0-only
#define __AVR_ATmega328P__

#include <avr/io.h>
#include "pwm.h"

void set_motorsA_backwards()
{
	PORTD |= (1<<PD2);
	PORTD &= ~(1<<PD3);
}
void set_motorsA_forward()
{
	PORTD |= (1<<PD3);
	PORTD &= ~(1<<PD2);
}
void set_motorsB_backwards()
{
	PORTD |= (1<<PD4);
	PORTD &= ~(1<<PD5);
}
void set_motorsB_forward()
{
	PORTD |= (1<<PD5);
	PORTD &= ~(1<<PD4);
}
void toycar_set_spd_direction(unsigned int speed, unsigned char direction)
{
	set_duty_ocr1AB(speed);
	if (direction == 'f')
	{
		set_motorsA_forward();
		set_motorsB_forward();
	}
	else if (direction == 'b')
	{
		set_motorsA_backwards();
		set_motorsB_backwards();
	}
	else if (direction == 'r')
	{
		set_motorsA_forward();
		set_motorsB_backwards();
	}
	else if (direction == 'l')
	{
		set_motorsA_backwards();
		set_motorsB_forward();
	}
}
