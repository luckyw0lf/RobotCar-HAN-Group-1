#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <stdint.h>

void timer1_init(void);
void trigger_pulse(void);
uint32_t get_distance(void);
void ultrasonic_init(void);

#endif