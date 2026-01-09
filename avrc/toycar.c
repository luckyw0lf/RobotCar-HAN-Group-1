//GPL-3.0-only
#define __AVR_ATmega328P__

#include <avr/io.h>
#include "pwm.h"

void set_motorsA_backwards()
{
	PORTC |= (1<<PC4);
	PORTC &= ~(1<<PC3);
}
void set_motorsA_forward()
{
	PORTC |= (1<<PC3);
	PORTC &= ~(1<<PC4);
}
void set_motorsB_backwards()
{
	PORTC |= (1<<PC2);
	PORTC &= ~(1<<PC1);
}
void set_motorsB_forward()
{
	PORTC |= (1<<PC1);
	PORTC &= ~(1<<PC2);
}
void toycar_set_spd_direction(unsigned int speed, unsigned char direction)
{
	set_duty_ocr0B(speed);
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
