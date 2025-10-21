#include <Arduino.h>
#include "pins.h"
#include "motor.h"
#include "bluetooth.h"

// Motor speed settings - will be updated from app
static int currentSpeed = 200;  // Default speed (0-255)
static int turnSpeed = 180;
static int diagonalSpeed = 170;

// Command buffer
static char commandBuffer[10];
static int bufferIndex = 0;

void bluetoothInit(void) {
    Serial.begin(9600);
}

// Function to check if a string is a number
int isNumber(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return 0;  // Not a number
        }
        i++;
    }
    return 1;  // Is a number
}

// Function to convert string to integer
int stringToInt(char* str) {
    int result = 0;
    int i = 0;
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

void processCommand(char* command) {
    if (isNumber(command)) {
        int speedLevel = stringToInt(command);
        if (speedLevel >= 0 && speedLevel <= 10) {
            currentSpeed = (speedLevel * 255) / 10;
            turnSpeed = (currentSpeed * 9) / 10;      // 90% of current speed
            diagonalSpeed = (currentSpeed * 85) / 100; // 85% of current speed
        }
        return;
    }
    
    // Movement commands
    if (command[0] == 'F' && command[1] == '\0') {
        // Forward
        forward(currentSpeed);
        
    } else if (command[0] == 'B' && command[1] == '\0') {
        // Backward
        backwards(currentSpeed);
        
    } else if (command[0] == 'L' && command[1] == '\0') {
        // Turn Left
        turnLeft(turnSpeed);
        
    } else if (command[0] == 'R' && command[1] == '\0') {
        // Turn Right
        turnRight(turnSpeed);
        
    } else if (command[0] == 'F' && command[1] == 'L' && command[2] == '\0') {
        // Forward Left (diagonal)
        leftMotor(diagonalSpeed / 2);
        rightMotor(diagonalSpeed);
        
    } else if (command[0] == 'F' && command[1] == 'R' && command[2] == '\0') {
        // Forward Right (diagonal)
        leftMotor(diagonalSpeed);
        rightMotor(diagonalSpeed / 2);
        
    } else if (command[0] == 'B' && command[1] == 'L' && command[2] == '\0') {
        // Backward Left (diagonal)
        leftMotor(-diagonalSpeed / 2);
        rightMotor(-diagonalSpeed);
        
    } else if (command[0] == 'B' && command[1] == 'R' && command[2] == '\0') {
        // Backward Right (diagonal)
        leftMotor(-diagonalSpeed);
        rightMotor(-diagonalSpeed / 2);
        
    } else if (command[0] == 'S' && command[1] == '\0') {
        // Stop
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

int getCurrentSpeed(void) {
    return currentSpeed;
}