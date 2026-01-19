#define F_CPU 16000000UL
// #define MILLIS_TIMER TIMER2_COMPA_vect
#include "../avrc/button.h"
#include "../avrc/uart.h"

volatile char mode = 0;

enum MODES {
    BLUETOOTH,
    ULTRASONIC,
    LINE,
};
int main(void) {
    init_usart_async_normal_rxtx(9600, 8, 1);
    initButton();

    for(;;){
        checkButton();

        switch (mode) {
        case BLUETOOTH:
            uart_putstr("B");
            break;
        case ULTRASONIC:
            uart_putstr("U");
            break;
        case LINE:
            uart_putstr("L");
            break;
        default:
            break;
        }
    }
}
