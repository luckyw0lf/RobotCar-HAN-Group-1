#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#include "../avrc/hcsr04.h"
#include "../avrc/uart.h"
#include <avr/io.h>
#include <util/atomic.h>

extern volatile unsigned int hcsr04_distance_cm_PCINT2;	//pd5
extern volatile unsigned int hcsr04_distance_cm_PCINT1;	//pc5
extern volatile unsigned int hcsr04_distance_cm_PCINT0;	//pb5

volatile unsigned char mode = 0;
ISR(USART_RX_vect)
{
	mode = UDR0-48;
	init_hcsr04_edges();
}
int main(void)
{
	//set timer1 pwm pin as output
	DDRB = (1<<PB1);

	init_hcsr04();
	init_usart_async_normal_rxtx(9600, 8, 1);
	enable_usart_rx_isr();
	sei();

	while(1)
	{
		if (hcsr04_distance_cm_PCINT2 != 0)
		{
			uart_putstr("PCINT2 / PD5 = ");
			uart_putnbr(hcsr04_distance_cm_PCINT2);
			uart_putchar('\n');
			hcsr04_distance_cm_PCINT2 = 0;
		}
		else if (hcsr04_distance_cm_PCINT1 != 0)
		{
			uart_putstr("PCINT1 / PC5 = ");
			uart_putnbr(hcsr04_distance_cm_PCINT1);
			uart_putchar('\n');
		}
		else if (hcsr04_distance_cm_PCINT0 != 0)
		{
			uart_putstr("PCINT0 / PB5 = ");
			uart_putnbr(hcsr04_distance_cm_PCINT0);
			uart_putchar('\n');
		}
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			hcsr04_distance_cm_PCINT1 = 0;
			hcsr04_distance_cm_PCINT0 = 0;
		}
	}
}
