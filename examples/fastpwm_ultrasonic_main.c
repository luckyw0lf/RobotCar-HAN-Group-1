#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#include "include/hcsr04.h"
#include "include/uart.h"
#include <avr/io.h>

extern volatile unsigned int hcsr04_distance_cm;
int main(void)
{
	DDRB = (1<<PB1);
	hcsr04_init();
	init_usart_async_normal_rxtx(9600, 8, 1);
	sei();
	while(1)
	{
			uart_putnbr(hcsr04_distance_cm);
			uart_putchar('\n');
	}
}
