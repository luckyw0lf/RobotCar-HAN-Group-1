#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "millis.h"
#include "uart.h"
#include "ultrasonic.h"

int main(void)
{
	unsigned long start;
	
	millis_init();
	init_usart_async_normal_rxtx(9600, 8, 1);
	ultrasonic_init();
	sei();
	
	uart_putstr("PLEASE OUTPUT VALUES\r\n");
	uart_putstr("distance ...\r\n\r\n");
	
	while (1)
	{
		uint32_t dist = get_distance();
		
		if (dist == 0)
		{
			uart_putstr("No echo received \r\n");
		}
		else if (dist > 400)
		{
			uart_putstr(" (>400cm)\r\n");
		}
		else
		{
			uart_putstr("Distance: ");
			uart_putnbr(dist);
			uart_putstr(" cm\r\n");
		}
		
		start = millis();
		while (millis() - start < 500);
	}
	
	return 0;
}