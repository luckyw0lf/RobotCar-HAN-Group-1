#include <Arduino.h>
#include <pins.h>
#include <motor.h>

void setup() {
  pinMode(MOTOR_LEFT_P, OUTPUT);
  pinMode(MOTOR_LEFT_N, OUTPUT);
  pinMode(MOTOR_RIGHT_P, OUTPUT);
  pinMode(MOTOR_RIGHT_N, OUTPUT);

  pinMode(LED_LEFT_OUTSIDE, INPUT);
  pinMode(LED_LEFT_INSIDE, INPUT);
  pinMode(LED_RIGHT_INSIDE, INPUT);
  pinMode(LED_RIGHT_OUTSIDE, INPUT);

  Serial.begin(9600);
}

void loop() {
  turnRight(90); // 0-255 max 
  delay(1000);
  emergencyStop();
  delay(1000);
  turnLeft(90);
  delay(1000);
  emergencyStop();
  delay(1000);
  forward(90);
  delay(2000);
  emergencyStop();
  delay(5000);
}
