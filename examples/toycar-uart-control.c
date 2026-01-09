#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#define RXBUF 16
#define PWMFREQ 250
#define PWMPRESCALER 256


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "../avrc/uart.h"
#include "../avrc/pwm.h"
#include "../avrc/toycar.h"

//format: 9f\n\0
//format: 4l\n\0
char global_buf[RXBUF];
volatile unsigned char global_i = 0;

//available duty values
unsigned int map[10] = {0, 50, 75, 100, 125, 150, 175, 200, 225, 249};

ISR(USART_RX_vect)
{
	if (global_i < RXBUF)
	{
		global_buf[global_i++] = UDR0;

		if (global_buf[global_i-1] == '\n' || global_i >= RXBUF-1)
		{
			toycar_set_spd_direction(map[global_buf[0]-48], global_buf[1]);
			global_i = 0;
		}
	}
}

int main(void)
{
	DDRD = (1<<PD5)|(1<<PD6);	//PWM(motors)

	DDRC = (1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4); //motors

	init_fastpwm_ocr0a(PWMPRESCALER);
	set_top_in_ocr0a(249);

	init_usart_async_normal_rxtx(9600, 8, 1);
	enable_usart_rx_isr();

	sei();
	while (1)
	{
		;
	}
}
