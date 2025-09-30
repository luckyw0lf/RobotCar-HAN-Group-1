#include <Arduino.h>
#include <pins.h>

int getDrivingDirection(){
    int LO = digitalRead(LED_LEFT_OUTSIDE); // -1
    int LI = digitalRead(LED_LEFT_INSIDE); // -.5
    int RI = digitalRead(LED_RIGHT_INSIDE); // .5
    int RO = digitalRead(LED_RIGHT_OUTSIDE);// 1

    if(LO || RO){
        return LO * -1 + RO * 1;
    }

    if(LI || RI){
        return LI * -.5 + RI * .5; 
    }

    return 0;
}