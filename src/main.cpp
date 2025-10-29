#include <Arduino.h>
#include <pins.h>
#include <motor.h>
#include <bluetooth.h>
#include <ultrasonic.h>

void setup() {
  // Motor pins
  pinMode(MOTOR_LEFT_P, OUTPUT);
  pinMode(MOTOR_LEFT_N, OUTPUT);
  pinMode(MOTOR_RIGHT_P, OUTPUT);
  pinMode(MOTOR_RIGHT_N, OUTPUT);

  // LED/Sensor pins
  pinMode(LED_LEFT_OUTSIDE, INPUT);
  pinMode(LED_LEFT_INSIDE, INPUT);
  pinMode(LED_RIGHT_INSIDE, INPUT);
  pinMode(LED_RIGHT_OUTSIDE, INPUT);

  bluetoothInit();
  
  delay(1000); 
  bluetoothSend("Robot Ready");
}

void loop() {
  bluetoothUpdate();
  delay(10);
  obstacleAvoidance();
}