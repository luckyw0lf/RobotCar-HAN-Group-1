#include <Arduino.h>
#include <motor.h>

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  leftMotor(256);
  delay(200);
  leftMotor(0);
  delay(2000);
}

// put function definitions here:
int myFunction(int x, int y) {
  
}