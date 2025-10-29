#ifndef ULTRASONIC_H
#define ULTRASONIC_H

void ultrasonicInit(void);
int getDistance(void);  // Returns distance in cm
void obstacleAvoidance(void);  // Main obstacle avoidance logic

#endif