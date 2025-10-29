#include <Arduino.h>
#include "pins.h"
#include "motor.h"
#include "ultrasonic.h"

#define MIN_DISTANCE 10 // Minimum safe distance in cm
#define TURN_DURATION 300 // How long to turn (ms)

void ultrasonicInit(void) {
    pinMode(ULTRASONIC_TRIGGER, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);
}

int getDistance(void) {
    long duration;
    int distance;
    
    digitalWrite(ULTRASONIC_TRIGGER, LOW);
    delayMicroseconds(2);
    
    digitalWrite(ULTRASONIC_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER, LOW);
    
    duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000); 
    
    distance = duration * 0.0343 / 2;
    
    if (distance == 0) {
        return 999;
    }
    
    return distance;
}

void obstacleAvoidance(void) {
    int distance = getDistance();
    
    if (distance < MIN_DISTANCE && distance > 0) {
        emergencyStop();
        delay(200);
        
        backwards(150);
        delay(300);
        emergencyStop();
        delay(100);
        
        while (true) {
            // Turn right
            turnRight(180);
            delay(TURN_DURATION);
            emergencyStop();
            delay(100);
            
            distance = getDistance();
            
            if (distance >= MIN_DISTANCE) {

                break;
            }
            
        }
        
        // Path is clear, resume normal operation
    }
}