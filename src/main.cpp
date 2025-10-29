#include <Arduino.h>
#include <pins.h>
#include <motor.h>
#include "bluetooth.h"
#include <SoftwareSerial.h>

unsigned long oldTime;
unsigned long deltaTime;
unsigned long updateDelay;

void setup() {
  pinMode(MOTOR_LEFT_P, OUTPUT);
  pinMode(MOTOR_LEFT_N, OUTPUT);
  pinMode(MOTOR_RIGHT_P, OUTPUT);
  pinMode(MOTOR_RIGHT_N, OUTPUT);

  pinMode(LED_LEFT_OUTSIDE, INPUT);
  pinMode(LED_LEFT_INSIDE, INPUT);
  pinMode(LED_RIGHT_INSIDE, INPUT);
  pinMode(LED_RIGHT_OUTSIDE, INPUT);

    bluetoothInit();
}

void loop() {
  unsigned long now = millis();
  deltaTime = now - oldTime;
  oldTime = now;

  bluetoothUpdate();
  
  // if(updateDelay >= 100){
  //     // Check for bluetooth
  //     // Reset the delay timer.
  //     updateDelay = 0;
  // }
  // turnRight(90); // 0-255 max 
  // delay(1000);
  // emergencyStop();
  // delay(1000);
  // turnLeft(90);
  // delay(1000);
  // emergencyStop();
  // delay(1000);
  // forward(90);
  // delay(2000);
  // emergencyStop();
  // delay(5000);
}