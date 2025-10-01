#include <Arduino.h>
#include <pins.h>
#include <motor.h>

void leftMotor(int speed){
    analogWrite(MOTOR_LEFT_F, speed);
    digitalWrite(MOTOR_LEFT_B, LOW);
}
void leftDownMotor(int speed){
    analogWrite(MOTOR_DOWN_LEFT_F, speed);
    digitalWrite(MOTOR_DOWN_LEFT_B, LOW);
}
void rightMotor(int speed){
    analogWrite(MOTOR_RIGHT_F, speed);
    digitalWrite(MOTOR_RIGHT_B, LOW);
}
void rightDownMotor(int speed){
    analogWrite(MOTOR_DOWN_RIGHT_F, speed);
    digitalWrite(MOTOR_DOWN_RIGHT_B, LOW);
}
// functions to reverse polarity and reverse the motors
//B and F indicate Backwards or forwards basically it changes from +V and GND for forward
//and if you wand backwards you change the place at the +V and GND
void leftMotorRev(int speed){
  analogWrite(MOTOR_LEFT_B, speed);
  digitalWrite(MOTOR_LEFT_F, LOW);
}
void leftDownMotorRev(int speed){
  analogWrite(MOTOR_DOWN_LEFT_B, speed);
  digitalWrite(MOTOR_DOWN_LEFT_F, LOW);
}
void rightMotorRev(int speed){
  analogWrite(MOTOR_RIGHT_B, speed);
  digitalWrite(MOTOR_RIGHT_F, LOW);
}
void rightDownMotorRev(int speed){
  analogWrite(MOTOR_DOWN_RIGHT_B, speed);
  digitalWrite(MOTOR_DOWN_RIGHT_F, LOW);
}

//turn the car right
void turnRight(int speed) {
    analogWrite(MOTOR_LEFT_F, speed);
    digitalWrite(MOTOR_LEFT_B, LOW);

    analogWrite(MOTOR_RIGHT_F, 0);
    digitalWrite(MOTOR_RIGHT_B, HIGH);
}
//turn the car left 
void turnLeft(int speed) {
    analogWrite(MOTOR_LEFT_F, 0);
    digitalWrite(MOTOR_LEFT_B, HIGH);

    analogWrite(MOTOR_RIGHT_F, speed);
    digitalWrite(MOTOR_RIGHT_B, LOW);
}
//forward car movement
void forward(int speed){
    leftMotor(speed);
    leftDownMotor(speed);
    rightMotor(speed);
    rightDownMotor(speed);
}
//backwards car movement 
void backwards(int speed){

    leftMotorRev(speed);
    leftDownMotorRev(speed);
    rightMotorRev(speed);
    rightDownMotorRev(speed);
}
// stops all motors at the same time 
void emergencyStop() {
    analogWrite(MOTOR_LEFT_F, 0);
    digitalWrite(MOTOR_LEFT_B, LOW);

    analogWrite(MOTOR_RIGHT_F, 0);
    digitalWrite(MOTOR_RIGHT_B, LOW);

    analogWrite(MOTOR_DOWN_LEFT_F, 0);
    digitalWrite(MOTOR_DOWN_LEFT_B, LOW);

    analogWrite(MOTOR_DOWN_RIGHT_F, 0);
    digitalWrite(MOTOR_DOWN_RIGHT_B, LOW);
}
