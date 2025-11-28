//GPL-3.0-only
#define __AVR_ATmega328P__
//#define FREE_ADC_ISR

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#if defined FREE_ADC_ISR
volatile unsigned int result_adc;
ISR(ADC_vect)
{
	result_adc = ADC;
}
#endif
void adc_init(unsigned char prescaler)
{
	if (prescaler == 128)
		ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	else if (prescaler == 64)
	{
		ADCSRA = (1<<ADPS2)|(1<<ADPS1);
		ADCSRA &= ~(1<<ADPS0);
	}
	else if (prescaler == 32)
	{
		ADCSRA = (1<<ADPS2)|(1<<ADPS0);
		ADCSRA &= ~(1<<ADPS1);
	}
	else if (prescaler == 16)
	{
		ADCSRA = (1<<ADPS2);
		ADCSRA &= ~((1<<ADPS1)|(1<<ADPS0));
	}
	else if (prescaler == 8)
	{
		ADCSRA = (1<<ADPS1)|(1<<ADPS0);
		ADCSRA &= ~(1<<ADPS2);
	}
	else if (prescaler == 4)
	{
		ADCSRA = (1<<ADPS1);
		ADCSRA &= ~((1<<ADPS2)|(1<<ADPS0));
	}
	else
		ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); //set prescaler to 2
	
	ADMUX = (1<<REFS0);		//AVcc with external capacitor at AREF pin
	ADMUX &= ~(1<<REFS1);	//

	ADCSRA |= (1<<ADEN); //ADC enable
	ADCSRA &= ~(1<<ADSC); //do not start conversion
}
void adc_init_free(void)
{
	ADMUX = (1<<REFS0);		//AVcc with external capacitor at AREF pin
	ADMUX &= ~(1<<REFS1);	//
	ADCSRA = 255;
	ADCSRB = 0;
}
void adc_start(void)
{
	//start conversion
	ADCSRA |= (1<<ADSC);
}
void adc_wait(void)
{
	//wait for conversion to be done
	while((ADCSRA & (1<<ADSC)) != 0)
		{;}
}

void adc_start_and_wait(void)
{
	adc_start();
	adc_wait();
}
//TEMPERATURE SENSOR
void tempsensor_init(void)
{
	//1.1V ref, internal temperature sensor
	ADMUX = (1<<REFS1)|(1<<REFS0)|(1<<MUX3);
	//enable ADC, don't start conversion(yet)
	ADCSRA = (1<<ADEN)|(1<<ADPS2);
//	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
signed int tempsensor_result(signed int offset)
{
	signed int temperature_celcius;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//temperature_celcius = (signed int)((ADC - offset)/1.22);
		temperature_celcius = (signed int)(ADC - offset);
		return (temperature_celcius);
	}
}
