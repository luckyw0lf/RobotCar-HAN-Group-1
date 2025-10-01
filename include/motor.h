#ifndef MOTOR_H //header guards
#define MOTOR_H

// definitions of functions for forward driving on the motors
void leftMotor(int speed);
void leftDownMotor(int speed);
void RightMotor(int speed);
void RightDownMotor(int speed);
//definitions of functions for backwards driving on the motors
void leftMotorRev(int speed);
void leftDownMotorRev(int speed);
void RightMotorRev(int speed);
void RightDownMotorRev(int speed);

//movement for the car 
void turnLeft(int speed);
void turnRight(int speed);
void backwards(int speed);
void forward(int speed);

#endif