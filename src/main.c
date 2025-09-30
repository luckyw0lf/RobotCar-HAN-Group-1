#include <Arduino.h>
#include <pins.h>
#include <motor.h>

unsigned long oldTime;
unsigned long deltaTime;
unsigned long lineTimer;

void setup() {
  pinMode(MOTOR_LEFT_F, OUTPUT);
  pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(LED_LEFT_OUTSIDE, OUTPUT);
  pinMode(LED_LEFT_INSIDE, OUTPUT);
  pinMode(LED_RIGHT_INSIDE, OUTPUT);
  pinMode(LED_RIGHT_OUTSIDE, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  deltaTime = now - oldTime;
  oldTime = now;

  lineTimer += deltaTime;
  if(lineTimer >= 10){
    lineTimer = 0;


  }


  leftMotor(50);
  delay(2000);
  leftMotor(0);
  delay(2000);
}
