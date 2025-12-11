#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ultrasonic.h"
#include "millis.h"
#include "uart.h"

volatile uint16_t timer_ovf = 0; //counts how many times timer1 overflows
volatile uint16_t rising_edge = 0; // this stores the tcnt1 value when echo pin is high 
volatile uint16_t falling_edge = 0; // this stores the tcnt1 value when echo pin is low 
volatile uint8_t echo_flag = 0; //this is either 0/1 because it detects when the failing edge is completed so the cycle is done

void timer1_init()
{
	TCCR1A = 0x00; //timer1 normal mode 
	TCCR1B = (1 << CS11); // prescaler 8 (010) / 16mhz : 8 = 2mhz= 1/2000000 = 0.5 microsecs per timer1 tick
	TIMSK1 = (1 << TOIE1); // enable overflow of timer1 interupt
}

void trigger_pulse() // this function creates the 10microseconds pulse
{
    unsigned long start = 0;
    
    PORTD &= ~(1 << PD3); //set to low
    start = micros();
    while (micros() - start < 2);
    
    PORTD |= (1 << PD3); // set to high
    start = micros();
    while (micros() - start < 10); //this is the loop that counts that the pulse was exactly 10 microseconds
    
    PORTD &= ~(1 << PD3); //again set to low to finish the pulse
}

ISR(TIMER1_OVF_vect)
{
	timer_ovf++;
}

ISR(INT0_vect)
{
	if (PIND & (1 << PD2))// check if pd2 high if so register the rising edge and reset timer overflow
	{
		rising_edge = TCNT1;
		timer_ovf = 0; // this is set to 0 because of line 69 because if overflowed its 1
	}
	else
	{
		falling_edge = TCNT1; // register the falling edge and flag the falling edge for a complete cycle
		echo_flag = 1;
	}
}

uint32_t get_distance()
{
	uint32_t pulse_width;
	uint32_t distance;
	unsigned long timeout_start;

	echo_flag = 0; //reset flag
	trigger_pulse();
	
	timeout_start = millis();
	while (!echo_flag && (millis() - timeout_start < 100)); //wait until flag is 1 or 100 microseconds have passed
	
	if (!echo_flag)
		return 0;
	
	pulse_width = (timer_ovf * 65536UL) + falling_edge - rising_edge;
     //compute pulse width in timing ticks 
    //(timer_ovf * 65536UL) this is here because if pulese is long enough to overflow we will get a negative value 
    //this basically assures that no mater what we always get the positive value because max is 65535 
    //even with long pules so even with rising edge 64000(because its started just before it overflows)
    //then overflow happens timer is reset to 0 and falling edge is 3000 for example then we will have a negative value
    // but with a value bigger that that we assure a postive one because 
    // 


	distance = pulse_width / 116; 
    // the value is 116 because timer tick is 0.5micro seconds sound travels 0.034 cm/microsecs
    //and because its a round trip it needs to be divided by 2 so the formula is 
    //distance = timerticks *0.5*0.034/2 = timerticks / 116;
    //1 cm = 1 /0.0085 = 116 
	
	return distance;
}

void ultrasonic_init()
{
	DDRD |= (1 << PD3); // trigger pd2 as output
	DDRD &= ~(1 << PD2); // echo pd3 as input
	PORTD |= (1 << PD2); // this is for pull up resistance
	
	EICRA = (1 << ISC00); //external interupt control register is set to to (01) this means on any change to detect rising and falling edge
	EIMSK = (1 << INT0); //enable interupt
	
	timer1_init();
}