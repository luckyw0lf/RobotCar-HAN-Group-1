#include <Arduino.h>
#include <pins.h>

int getDrivingDirection(){
    int Left_Outside = digitalRead(LED_LEFT_OUTSIDE); // -1
    int Left_Inside = digitalRead(LED_LEFT_INSIDE); // -.5
    int Right_Inside = digitalRead(LED_RIGHT_INSIDE); // .5
    int Right_Outside = digitalRead(LED_RIGHT_OUTSIDE);// 1

    if(Left_Outside || Right_Outside){
        return Left_Outside * -1.0f + Right_Outside * 1.0f;
    }

    if(Left_Inside || Right_Inside){
        return Left_Inside * -.5f + Right_Inside * .5f; 
    }

    return 0;
}