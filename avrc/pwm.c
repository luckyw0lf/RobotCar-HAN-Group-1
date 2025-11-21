//GPL-3.0-only
#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/atomic.h>

unsigned int ICR1_val(unsigned long f_cpu, unsigned long f_pwm, unsigned int prescaler)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//TOP = (F_CPU / (F_PWM * N)) - 1
		return ((f_cpu / (f_pwm * prescaler)) - 1);
	}
}
void init_fastpwm_icr1(unsigned int prescaler)
{
	//fastpwm with TOP in ICR1
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13)|(1<<WGM12);

	if (prescaler == 1024)
	{
		TCCR1B |= (1<<CS12)|(1<<CS10);
		TCCR1B &= ~(1<<CS11);
	}
	else if (prescaler == 256)
	{
		TCCR1B |= (1<<CS12);
		TCCR1B &= ~((1<<CS11)|(1<<CS10));
	}
	else if (prescaler == 64)
	{
		TCCR1B |= (1<<CS11)|(1<<CS10);
		TCCR1B &= ~(1<<CS12);
	}
	else if (prescaler == 8)
	{
		TCCR1B |= (1<<CS11);
		TCCR1B &= ~((1<<CS12)|(1<<CS10));

	}
	else if (prescaler == 0)
	{
		TCCR1B &= ~((1<<CS12)|(1<<CS11)|(1<<CS10));
	}
	else
	{
		//(prescaler == 1)
		TCCR1B |= (1<<CS10);
		TCCR1B &= ~((1<<CS12)|(1<<CS11));
	}
}

void set_top_in_icr1(unsigned int ICR1_value)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		ICR1 = ICR1_value;
	}
}

void set_duty_ocr1A(unsigned int duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//Clear OC0A on compare match, set OC0A at BOTTOM,
		//(non-inverting mode).
		TCCR1A |= (1<<COM1A1);
		TCCR1A &= ~(1<<COM1A0);

		OCR1A = duty;
	}
}
void set_duty_ocr1B(unsigned int duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TCCR1A |= (1<<COM1B1);
		TCCR1A &= ~(1<<COM1B0);

		OCR1B = duty;
	}
}
void set_duty_ocr1AB(unsigned int duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TCCR1A |= (1<<COM1A1);
		TCCR1A &= ~(1<<COM1A0);

		TCCR1A |= (1<<COM1B1);
		TCCR1A &= ~(1<<COM1B0);

		OCR1A = duty;
		OCR1B = duty;
	}
}

void set_duty_inverted_ocr1A(unsigned int duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//Set OC1A on compare match, clear OC1A at BOTTOM
		//(inverting mode)
		TCCR1A |= (1<<COM1A1);
		TCCR1A |= (1<<COM1A0);

		OCR1A = duty;
	}
}
void set_duty_inverted_ocr1B(unsigned int duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TCCR1A |= (1<<COM1B1);
		TCCR1A |= (1<<COM1B0);

		OCR1B = duty;
	}
}
void set_duty_inverted_ocr1AB(unsigned int duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TCCR1A |= (1<<COM1A1);
		TCCR1A |= (1<<COM1A0);

		TCCR1A |= (1<<COM1B1);
		TCCR1A |= (1<<COM1B0);

		OCR1A = duty;
		OCR1B = duty;
	}
}
