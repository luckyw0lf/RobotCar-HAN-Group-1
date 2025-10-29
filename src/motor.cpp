#include <Arduino.h>
#include <pins.h>
#include <motor.h>


void leftMotor(int speed){
    if(speed < 0){
        digitalWrite(MOTOR_LEFT_P, LOW);
        analogWrite(MOTOR_LEFT_N, -speed);
        return;
    }
    analogWrite(MOTOR_LEFT_P, speed);
    digitalWrite(MOTOR_LEFT_N, LOW);
}

void rightMotor(int speed){
    if(speed < 0){
        digitalWrite(MOTOR_RIGHT_P, LOW);
        analogWrite(MOTOR_RIGHT_N, -speed);

        return;
    }
    analogWrite(MOTOR_RIGHT_P, speed);
    digitalWrite(MOTOR_RIGHT_N, LOW);
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
// stops all motors at the same time 
void emergencyStop() {
    leftMotor(0);
    rightMotor(0);
}
