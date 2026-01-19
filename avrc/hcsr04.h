#ifndef HCSR04_H_ 
#define HCSR04_H_ 
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "pwm.h"

#include "uart.h"

extern volatile unsigned char mode;

//BEGIN PCINT2
volatile unsigned int hcsr04_distance_cm_PCINT2 = 0;
volatile signed char edge_PCINT2 = 1;
volatile unsigned long timer_start_PCINT2 = 0;	//make them global?
volatile unsigned long timer_stop_PCINT2 = 0;

void ultrasonic_PCINT2(void)
{
		if (1 == edge_PCINT2 )//rising edge_PCINT2
		{
			timer_start_PCINT2 = TCNT1; //on rising edge_PCINT2
		}
		else	//falling edge_PCINT2
		{
			timer_stop_PCINT2 = TCNT1;
			hcsr04_distance_cm_PCINT2 = (((timer_stop_PCINT2 - timer_start_PCINT2)*4)/58);
		}
		edge_PCINT2 *= -1;
}
void ir_PCINT2(void)
{
	//to be implemented...
	uart_putstr("ir_PCINT2\n");
}
void null_PCINT2(void)
{
	//null, should not be called
	uart_putstr("null_PCINT2\n");
}
void (*jumptable_PCINT2[])() = {null_PCINT2, ultrasonic_PCINT2, ir_PCINT2};

ISR(PCINT2_vect)
{
	jumptable_PCINT2[mode]();
}
//END PCINT2

//BEGIN PCINT1
volatile unsigned int hcsr04_distance_cm_PCINT1 = 0;
volatile signed char edge_PCINT1 = 1;
volatile unsigned long timer_start_PCINT1 = 0;	//make them global?
volatile unsigned long timer_stop_PCINT1 = 0;

void ultrasonic_PCINT1(void)
{
		if (1 == edge_PCINT1 )//rising edge_PCINT1
		{
			timer_start_PCINT1 = TCNT1; //on rising edge_PCINT1
		}
		else	//falling edge_PCINT1
		{
			timer_stop_PCINT1 = TCNT1;
			hcsr04_distance_cm_PCINT1 = (((timer_stop_PCINT1 - timer_start_PCINT1)*4)/58);
		}
		edge_PCINT1 *= -1; }
void ir_PCINT1(void)
{
	uart_putstr("ir_PCINT1\n");
}
void null_PCINT1(void)
{
	//null, should not be called
	uart_putstr("null_PCINT1\n");
}
void (*jumptable_PCINT1[])() = {null_PCINT1, ultrasonic_PCINT1, ir_PCINT1};

ISR(PCINT1_vect)
{
	jumptable_PCINT1[mode]();
}
//END PCINT1

//BEGIN PCINT0
volatile unsigned int hcsr04_distance_cm_PCINT0 = 0;
volatile signed char edge_PCINT0 = 1;
volatile unsigned long timer_start_PCINT0 = 0;	//make them global?
volatile unsigned long timer_stop_PCINT0 = 0;

void ultrasonic_PCINT0(void)
{
		if (1 == edge_PCINT0 )//rising edge_PCINT0
		{
			timer_start_PCINT0 = TCNT1; //on rising edge_PCINT0
		}
		else	//falling edge_PCINT0
		{
			timer_stop_PCINT0 = TCNT1;
			hcsr04_distance_cm_PCINT0 = (((timer_stop_PCINT0 - timer_start_PCINT0)*4)/58);
		}
		edge_PCINT0 *= -1;
}
void ir_PCINT0(void)
{
	uart_putstr("ir_PCINT0\n");
}
void null_PCINT0(void)
{
	//null, should not be called
	uart_putstr("null_PCINT0\n");
}
void (*jumptable_PCINT0[])() = {null_PCINT0, ultrasonic_PCINT0, ir_PCINT0};

ISR(PCINT0_vect)
{
	jumptable_PCINT0[mode]();
}
//END PCINT0

void init_hcsr04(void); 

void enable_hcsr04(void);

void init_hcsr04_edges(void);

void enable_ir(void);

void enable_pcinterrupts(void);
void disable_sensors(void);
#endif /* HCSR04_H_ */
