#include <Arduino.h>
#include <pins.h>
#include <motor.h>


void leftMotor(int speed){
    if(speed < 0){
        analogWrite(MOTOR_LEFT_P, -speed);
        digitalWrite(MOTOR_LEFT_N, LOW);
        return;
    }
    digitalWrite(MOTOR_LEFT_P, LOW);
    analogWrite(MOTOR_LEFT_N, speed);
}

void rightMotor(int speed){
    if(speed < 0){
        analogWrite(MOTOR_RIGHT_P, -speed);
        digitalWrite(MOTOR_RIGHT_N, LOW);

        return;
    }
    digitalWrite(MOTOR_RIGHT_P, LOW);
    analogWrite(MOTOR_RIGHT_N, speed);
}

//turn the car right
void turnRight(int speed) {
    leftMotor(speed);
    rightMotor(-speed);
}
//turn the car left 
void turnLeft(int speed) {
    leftMotor(-speed);
    rightMotor(speed);
}
//forward car movement
void forward(int speed){
    leftMotor(speed);
    rightMotor(speed);
}
//backwards car movement 
void backwards(int speed){
    leftMotor(-speed);
    rightMotor(-speed);
}

void vectorTurnRight(int speed, int diff = 30) {
    leftMotor(speed);
    rightMotor(speed - diff);
}

void vectorTurnLeft(int speed, int diff = 30) {
    leftMotor(speed - diff);
    rightMotor(speed);
}
// stops all motors at the same time 
void emergencyStop() {
    leftMotor(0);
    rightMotor(0);
}

