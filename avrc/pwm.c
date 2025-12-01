//GPL-3.0-only
#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/atomic.h>

unsigned int pwm_ICRn_val(unsigned long f_cpu, unsigned long f_pwm, unsigned int prescaler)
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
	TCCR1A = (1<<WGM11);
	TCCR1B = (1<<WGM13)|(1<<WGM12);

	if (prescaler == 1024)
		TCCR1B |= (1<<CS12)|(1<<CS10);
	else if (prescaler == 256)
		TCCR1B |= (1<<CS12);
	else if (prescaler == 64)
		TCCR1B |= (1<<CS11)|(1<<CS10);
	else if (prescaler == 8)
		TCCR1B |= (1<<CS11);
	else if (prescaler == 0)
		;	//No clock source (Timer/Counter stopped).
	else
		TCCR1B |= (1<<CS10);	//prescaler 1
}
void init_fastpwm_ocr0a(unsigned int prescaler)
{
	//fastpwm with TOP in OCR0
	TCCR0A = (1<<WGM01)|(1<<WGM00);
	TCCR0B = (1<<WGM02);

	if (prescaler == 1024)
		TCCR0B |= (1<<CS02)|(1<<CS00);
	else if (prescaler == 256)
		TCCR0B |= (1<<CS02);
	else if (prescaler == 64)
		TCCR0B |= (1<<CS01)|(1<<CS00);
	else if (prescaler == 8)
		TCCR0B |= (1<<CS01);
	else if (prescaler == 0)
		;	//No clock source (Timer/Counter stopped).
	else
		TCCR0B |= (1<<CS00);	//prescaler 1
}
void set_top_in_icr1(unsigned int ICR1_value)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		ICR1 = ICR1_value;
	}
}
void set_top_in_ocr0a(unsigned int ICR1_value)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//PD6
		OCR0A = ICR1_value;
	}
}
//this is for FastPWM on TIMER1
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
//END for FastPWM on TIMER1

//this is for FastPWM on TIMER0
void set_duty_ocr0B(unsigned char duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TCCR0A |= (1<<COM0B1);
		TCCR0A &= ~(1<<COM0B0);

		OCR0B = duty;
	}
}
void set_duty_inverted_ocr0B(unsigned char duty)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TCCR0A |= (1<<COM0B1);
		TCCR0A |= (1<<COM0B0);

		OCR0B = duty;
	}
}
//END for FastPWM on TIMER0
