#include <Arduino.h>
#include <pins.h>
#include <motor.h>

bool left_sensor = false;
bool right_sensor = false;
bool center_sensor = false;


void updateLineSensors(){
    // When black, returns true
    left_sensor = digitalRead(LED_LEFT);
    right_sensor = digitalRead(LED_RIGHT);
    center_sensor = digitalRead(LED_CENTER);

    if(center_sensor && !right_sensor && !left_sensor){
        forward(75);
        return;
    }

    if(!center_sensor && !right_sensor && !left_sensor){
        forward(75);
        return;
    }

    if(center_sensor && right_sensor){
        turnRight(150);
        return;
    }

    if(center_sensor && left_sensor){
        turnLeft(150);
        return;
    }

    if(right_sensor){
        turnRight(150);
        return;
    }

    if(left_sensor){
        turnLeft(150);
        return;
    }

    emergencyStop();
    
}

