//GPL-3.0-only
#ifndef UART_H_
 #define UART_H_

void enable_usart_rx_isr(void);
void disable_usart_rx_isr(void);
//#include "uart.h"

//tx functions, they all work!
//
//init_usart_async_normal_rxtx function expects
//valid arguments for framesize and stopsize
//for atmega328p valid framsizes are 5, 6, 7, 8 and 9
//for atmega328p valid stopsizes are 1 and 2
//refer to a datasheet P19.1 "USART0 Features"
//
//init_usart_async_normal_rxtx(9600, 8, 1) for 9600 8N1
//init_usart_async_normal_rxtx(28800, 5, 2) for 28.8k 5N2
//
//todo: implement parity control
void init_usart_async_normal_rxtx(unsigned long rate, unsigned char framesize, unsigned char stopsize); 

//todo: 9bit output
void uart_putchar(unsigned char c); 

//print character in hexadecimal form over uart
void uart_puthex(unsigned char c); 

//print string over uart
void uart_putstr(char *str); 

void uart_putnstr(char *str, unsigned char n);

//send long long number over uart
void uart_putnbr(signed long long nb); 

//rx functions, they all work!

unsigned char uart_getchar(void);

//uart_getline function will get at maximum (2^8)-1 characters,
//write them into *buf, unless \n character is transmitted,
//and null-terminate the string

void uart_getline(char *buf, unsigned char size);

#endif // UART_H_
