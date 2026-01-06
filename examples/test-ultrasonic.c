#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#define RXBUF 16
#define PWMFREQ 250
#define PWMPRESCALER 256

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "../avrc/uart.h"
#include "../avrc/millis.h"
#include "../avrc/pwm.h"
#include "../avrc/toycar.h"
#include "../avrc/hcsr04.h"

#define MILLIS_TIMER TIMER2_COMPA_vect
extern volatile unsigned long timer;

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

extern volatile unsigned int hcsr04_distance_cm_PCINT2;	//PD5, right sensor
extern volatile unsigned int hcsr04_distance_cm_PCINT1;	//PB0, central sensor
extern volatile unsigned int hcsr04_distance_cm_PCINT0;	//PC5, left sensor


volatile unsigned char sensor_status = 0;
void logic_ultrasonic(unsigned char speed)
{
	//00010000	distance == 16, safe
	//!(16>>4), aka !00000001, aka 0000000, safe
	//
	//00010001	distance == 17, safe
	//!(17>>4), aka !00000001, aka 0000000, safe
	//
	//00000111	distance == 7, unsafe
	//!(7>>4), aka !00000000  aka 0000001, unsafe
	
	sensor_status = (!(hcsr04_distance_cm_PCINT2>>4))<<2;
	sensor_status |= (!(hcsr04_distance_cm_PCINT1>>4))<<1;
	sensor_status |= (!(hcsr04_distance_cm_PCINT0>>4))<<0;
ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
{
	switch (sensor_status)
	{
		case 0:
				//move forward
			uart_putchar('0');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'f');
		case 1:
				//obstacle on the left
				//TURN RIGHT
			uart_putchar('1');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'r');
		case 2:
				//obstacle in front
				//TURN 90 DEGREES left\right
			uart_putchar('2');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'r');
		case 3:
				//obstacle on left+front
				//TURN RIGHT
			uart_putchar('3');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'r');
		case 4:
				//obstacle on the right
				//TURN LEFT
			uart_putchar('4');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'l');
		case 5:
				//obstacle on right+left
				//TURN left\right
			uart_putchar('5');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'r');
		case 6:
				//obstacle on right+centre
				//TURN LEFT
			uart_putchar('6');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'l');
		case 7:
				//obstacle everywhere
				//TURN left\right
			uart_putchar('7');
			uart_putchar('\n');
		//	toycar_set_spd_direction(map[speed], 'r');
	}
}
}

#define MODE_BLUETOOTH 0
#define MODE_ULTRASONIC 1
#define MODE_LINETRACKING 2
volatile unsigned char mode = MODE_ULTRASONIC;	//should changed to zero in final main.c

int main(void)
{
	DDRD = (1<<PB1);	//PWM(ultrasonic)

	//DDRC = (1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5); //motors
	

//	init_fastpwm_ocr0a(PWMPRESCALER);
//	set_top_in_ocr0a(249);

	init_usart_async_normal_rxtx(9600, 8, 1);
	enable_usart_rx_isr();

//	init_millis_timer2();
	init_hcsr04();

	sei();
	unsigned char ultrasonic_speed = 5;
	while (1)
	{
		//check for a button input here
//				//stop motors
//				toycar_set_spd_direction(0, 'f');
				logic_ultrasonic(ultrasonic_speed);
	}
}
