#include <Arduino.h>
#include <pins.h>
#include <motor.h>

void setup() {
  pinMode(MOTOR_LEFT_F, OUTPUT);
  pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(MOTOR_RIGHT_F, OUTPUT);
  pinMode(MOTOR_RIGHT_B, OUTPUT);
  pinMode(MOTOR_DOWN_LEFT_F, OUTPUT);
  pinMode(MOTOR_DOWN_LEFT_B, OUTPUT);
  pinMode(MOTOR_DOWN_RIGHT_F, OUTPUT);
  pinMode(MOTOR_DOWN_RIGHT_B, OUTPUT);

  pinMode(LED_LEFT_OUTSIDE, INPUT);
  pinMode(LED_LEFT_INSIDE, INPUT);
  pinMode(LED_RIGHT_INSIDE, INPUT);
  pinMode(LED_RIGHT_OUTSIDE, INPUT);
}

void loop() {
  turnRight(150); // 0-255 max 
  delay(1000);
  emergencyStop(); // stops all motors at the same time 
  delay(1000);

  turnLeft(150);
  delay(1000);
  emergencyStop();
  delay(2000);
}
