#include <Arduino.h>
#include "pins.h"
#include "motor.h"
#include "bluetooth.h"

// Motor speed settings
#define NORMAL_SPEED 200
#define TURN_SPEED 180
#define DIAGONAL_SPEED 170

// Command buffer
static char commandBuffer[10];
static int bufferIndex = 0;

void bluetoothInit(void) {
    Serial.begin(9600);
}

void processCommand(char* command) {
    if (command[0] == 'F' && command[1] == '\0') {
        forward(NORMAL_SPEED);
        
    } else if (command[0] == 'B' && command[1] == '\0') {
        backwards(NORMAL_SPEED);
        
    } else if (command[0] == 'L' && command[1] == '\0') {
        turnLeft(TURN_SPEED);
        
    } else if (command[0] == 'R' && command[1] == '\0') {
        turnRight(TURN_SPEED);
        
    } else if (command[0] == 'F' && command[1] == 'L' && command[2] == '\0') {
        leftMotor(DIAGONAL_SPEED / 2);
        leftDownMotor(DIAGONAL_SPEED / 2);
        RightMotor(DIAGONAL_SPEED);
        RightDownMotor(DIAGONAL_SPEED);
        
    } else if (command[0] == 'F' && command[1] == 'R' && command[2] == '\0') {
        leftMotor(DIAGONAL_SPEED);
        leftDownMotor(DIAGONAL_SPEED);
        RightMotor(DIAGONAL_SPEED / 2);
        RightDownMotor(DIAGONAL_SPEED / 2);
        
    } else if (command[0] == 'B' && command[1] == 'L' && command[2] == '\0') {
        leftMotorRev(DIAGONAL_SPEED / 2);
        leftDownMotorRev(DIAGONAL_SPEED / 2);
        RightMotorRev(DIAGONAL_SPEED);
        RightDownMotorRev(DIAGONAL_SPEED);
        
    } else if (command[0] == 'B' && command[1] == 'R' && command[2] == '\0') {
        leftMotorRev(DIAGONAL_SPEED);
        leftDownMotorRev(DIAGONAL_SPEED);
        RightMotorRev(DIAGONAL_SPEED / 2);
        RightDownMotorRev(DIAGONAL_SPEED / 2);
        
    } else if (command[0] == 'S' && command[1] == '\0') {
        emergencyStop();
    }
}

void bluetoothUpdate(void) {
    int available;
    char inChar;
    
    available = Serial.available();
    
    while (available > 0) {
        inChar = (char)Serial.read();
        
        if (inChar == '\n' || inChar == '\r') {
            if (bufferIndex > 0) {
                commandBuffer[bufferIndex] = '\0';
                processCommand(commandBuffer);
                bufferIndex = 0;
            }
        } else {
            if (bufferIndex < 9) {
                commandBuffer[bufferIndex] = inChar;
                bufferIndex++;
            } else {
                bufferIndex = 0;
            }
        }
        
        available = Serial.available();
    }
}

void bluetoothSend(char* message) {
    Serial.println(message);
}