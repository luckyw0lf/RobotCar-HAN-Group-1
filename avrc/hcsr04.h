#ifndef HCSR04_H_ 
#define HCSR04_H_ 
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "pwm.h"

//mode0 = bluetooth
//mode1 = ultrasonic
//mode2 = linetracking
extern volatile unsigned char mode;

void init_hcsr04(void);

//PCINT2 
volatile unsigned int hcsr04_distance_cm_PCINT2 = 0;
volatile signed char edge_PCINT2 = 1;
volatile unsigned long timer_start_PCINT2 = 0;
volatile unsigned long timer_stop_PCINT2 = 0;

void bluetooth_PCINT2(void)
{
	; //null, should not be called
}
void ultrasonic_PCINT2(void)
{
	if (1 == edge_PCINT2)//rising edge
	{
		timer_start_PCINT2 = TCNT1; //on rising edge
	}
	else	//falling edge
	{
		timer_stop_PCINT2 = TCNT1;
		hcsr04_distance_cm_PCINT2 = (((timer_stop_PCINT2 - timer_start_PCINT2)*4)/58);
	}
	edge_PCINT2 *= -1;
}
void linetracking_PCINT2(void)
{
	; //to be implemented
}
void (*jumptable_PCINT2[])() = {bluetooth_PCINT2, ultrasonic_PCINT2, linetracking_PCINT2};

ISR(PCINT2_vect)
{
	jumptable_PCINT2[mode]();
}
//END PCINT2

//PCINT1 
volatile unsigned int hcsr04_distance_cm_PCINT1 = 0;
volatile signed char edge_PCINT1 = 1;
volatile unsigned long timer_start_PCINT1 = 0;
volatile unsigned long timer_stop_PCINT1 = 0;

void bluetooth_PCINT1(void)
{
	; //null, should not be called
}
void ultrasonic_PCINT1(void)
{
	if (1 == edge_PCINT1)//rising edge
	{
		timer_start_PCINT1 = TCNT1; //on rising edge
	}
	else	//falling edge
	{
		timer_stop_PCINT1 = TCNT1;
		hcsr04_distance_cm_PCINT1 = (((timer_stop_PCINT1 - timer_start_PCINT1)*4)/58);
	}
	edge_PCINT1 *= -1;
}
void linetracking_PCINT1(void)
{
	; //to be implemented
}
void (*jumptable_PCINT1[])() = {bluetooth_PCINT1, ultrasonic_PCINT1, linetracking_PCINT1};

ISR(PCINT1_vect)
{
	jumptable_PCINT1[mode]();
}
//END PCINT1 

//PCINT0 
volatile unsigned int hcsr04_distance_cm_PCINT0 = 0;
volatile signed char edge_PCINT0 = 1;
volatile unsigned long timer_start_PCINT0 = 0;
volatile unsigned long timer_stop_PCINT0 = 0;

void bluetooth_PCINT0(void)
{
	; //null, should not be called
}
void ultrasonic_PCINT0(void)
{
	if (1 == edge_PCINT0)//rising edge
	{
		timer_start_PCINT0 = TCNT1; //on rising edge
	}
	else	//falling edge
	{
		timer_stop_PCINT0 = TCNT1;
		hcsr04_distance_cm_PCINT0 = (((timer_stop_PCINT0 - timer_start_PCINT0)*4)/58);
	}
	edge_PCINT0 *= -1;
}
void linetracking_PCINT0(void)
{
	; //to be implemented
}
void (*jumptable_PCINT0[])() = {bluetooth_PCINT0, ultrasonic_PCINT0, linetracking_PCINT0};
ISR(PCINT0_vect)
{
	jumptable_PCINT0[mode]();
}
//END PCINT0 
#endif /* HCSR04_H_ */
