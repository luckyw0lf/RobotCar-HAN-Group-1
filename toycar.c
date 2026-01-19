#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#define RXBUF 16
#define PWMFREQ 250
#define PWMPRESCALER 256

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "avrc/uart.h"
#include "avrc/millis.h"
#include "avrc/pwm.h"
#include "avrc/toycar.h"
#include "avrc/hcsr04.h"
volatile unsigned char mode = 0;
#include "avrc/button.h"

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
extern volatile unsigned int hcsr04_distance_cm_PCINT1;	//PC0, central sensor
extern volatile unsigned int hcsr04_distance_cm_PCINT0;	//PB5, left sensor


volatile unsigned char sensor_status = 0;
void logic_ultrasonic(unsigned char speed)
{
	sensor_status = (!(hcsr04_distance_cm_PCINT2>>5))<<2;
	sensor_status |= (!(hcsr04_distance_cm_PCINT1>>5))<<1;
	sensor_status |= (!(hcsr04_distance_cm_PCINT0>>5))<<0;

	switch (sensor_status)
	{
		case 0:
				//move forward
			toycar_set_spd_direction(map[speed], 'f');
			break;
		case 1:
				//obstacle on the left
				//TURN RIGHT
			toycar_set_spd_direction(map[speed+3], 'r');
			break;
		case 2:
				//obstacle in front
				//TURN 90 DEGREES left\right
			toycar_set_spd_direction(map[speed+3], 'r');
			break;
		case 3:
				//obstacle on left+front
				//TURN RIGHT
			toycar_set_spd_direction(map[speed+3], 'r');
			break;
		case 4:
				//obstacle on the right
				//TURN LEFT
			toycar_set_spd_direction(map[speed+3], 'l');
			break;
		case 5:
				//obstacle on right+left
				//TURN left\right
			toycar_set_spd_direction(map[speed+3], 'r');
			break;
		case 6:
				//obstacle on right+centre
				//TURN LEFT
			toycar_set_spd_direction(map[speed+3], 'l');
			break;
		case 7:
				//obstacle everywhere
				//TURN left\right
			toycar_set_spd_direction(map[speed+3], 'r');
			break;
	}

}
void logic_ir(unsigned char speed)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	sensor_status = (!(PINC & (1<<PC0)))<<2;	//right
	sensor_status |= (!(PIND & (1<<PD3)))<<1;	//left
	sensor_status |= (!(PINB & (1<<PB2)))<<0;	//middle

	uart_putstr("sensor_status = ");
	uart_putnbr(sensor_status);
	uart_putstr("\r\n");
	//HERE could be your jump table
	switch (sensor_status)
	{
		case 0:
				//no line detected?
			toycar_set_spd_direction(map[0], 'b');
			break;
		case 1:
		//should not happen
			toycar_set_spd_direction(map[speed], 'f');
			break;
		case 2:
			toycar_set_spd_direction(map[speed+1], 'r');
			break;
		case 3:
			toycar_set_spd_direction(map[speed+1], 'r');
			break;
		case 4:
				//obstacle on the right
				//TURN LEFT
			toycar_set_spd_direction(map[speed+1], 'l');
			break;
		case 5:
				//obstacle on right+left
				//TURN left\right
			toycar_set_spd_direction(map[speed+1], 'l');
			break;
		case 6:
				//obstacle on right+centre
				//TURN LEFT
			toycar_set_spd_direction(map[speed], 'f');
			break;
		case 7:
				//obstacle everywhere
				//TURN left\right
			toycar_set_spd_direction(map[speed], 'f');
			break;
	}
}
#define MODE_BLUETOOTH 0
#define MODE_ULTRASONIC 1
#define MODE_LINETRACKING 2


int main(void)
{
	DDRD = (1<<PD5);	//PWM(motors)
	DDRB = (1<<PB1);	//PWM(ultrasonic)

	DDRC = (1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4); //motors
	
	init_fastpwm_ocr0a(PWMPRESCALER);
	set_top_in_ocr0a(249);

	init_usart_async_normal_rxtx(9600, 8, 1);
	enable_usart_rx_isr();

	init_hcsr04();
	enable_hcsr04();
	enable_ir();
	enable_pcinterrupts();

  	init_millis_timer2();
	sei();

	unsigned char default_speed = 3;
	while (1)
	{
		checkButton();
		switch (mode)
		{
			case MODE_ULTRASONIC:
				logic_ultrasonic(default_speed);
				break;
			case MODE_LINETRACKING:
				logic_ir(default_speed);
			break;
					//to be impemented
			case MODE_BLUETOOTH:
			break;
					// do nothing
		}
	}
}
