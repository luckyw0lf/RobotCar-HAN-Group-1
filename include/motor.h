#ifndef MOTOR_H //header guards
#define MOTOR_H

// definitions of functions for forward driving on the motors
void leftMotor(int speed);
void rightMotor(int speed);

//movement for the car 
void turnLeft(int speed);
void turnRight(int speed);
void backwards(int speed);
void forward(int speed);

void vectorTurnLeft(int speed, int diff);
void vectorTurnRight(int speed, int diff);

// emergency stop
void emergencyStop();

#endif