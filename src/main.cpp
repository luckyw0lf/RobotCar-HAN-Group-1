#include <Arduino.h>
#include <pins.h>
#include <motor.h>
#include "bluetooth.h"
#include <SoftwareSerial.h>
#include <ultrasonic.h>
#include <line_sensor.h> 

unsigned long oldTime;
unsigned long deltaTime;
unsigned long updateDelay;
int mode = 0;                 
bool lastButtonState = HIGH;  
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; 

void setup() {
  // Motor pins
  pinMode(MOTOR_LEFT_P, OUTPUT);
  pinMode(MOTOR_LEFT_N, OUTPUT);
  pinMode(MOTOR_RIGHT_P, OUTPUT);
  pinMode(MOTOR_RIGHT_N, OUTPUT);
  
  pinMode(BUTTON_SWITCH, INPUT_PULLUP);

  bluetoothInit();
}

void checkButton() {
  int reading = digitalRead(BUTTON_SWITCH);

  // Debounce logic
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Button is stable
    if (reading == LOW && lastButtonState == HIGH) {
      mode++;
      if (mode > 2) mode = 0;
    }
  }
  
  lastButtonState = reading;
}

void loop() {
  unsigned long now = millis();
  deltaTime = now - oldTime;
  oldTime = now;
  
  checkButton();
  
  switch (mode) {
    case 0:
      bluetoothUpdate(); // Manual driving
      break;

    case 1:
      updateLineSensors(); // Line tracking
      break;

    case 2:
      obstacleAvoidance(); // Ultrasonic sensor 
      break;
  }
  
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