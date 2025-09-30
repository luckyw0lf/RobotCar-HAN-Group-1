#include <pins.h>
#include <Arduino.h>

void leftMotor(int speed){
    analogWrite(MOTOR_LEFT_F, speed);
    digitalWrite(MOTOR_LEFT_B, LOW);
}