//GPL-3.0-only
#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#define UBRR_async_normal(rate) ((F_CPU / (16*rate))-1)
#define UBRR_async_double(rate) ((F_CPU / (8*rate))-1)
#define UBRR_sync_master(rate) ((F_CPU / (2*rate))-1)

#include <avr/io.h>

void init_usart_async_normal_rxtx(unsigned long rate, unsigned char framesize, unsigned char stopsize)
{
	//overwrite previous configuration
	UCSR0B = 0;
	UCSR0C = 0;

	//set async mode
	UCSR0C &= ~((1<<UMSEL01)|(1<<UMSEL00));
	//todo: set normal mode

	//set stop bits
	//here could be your if (stopsize == 2)
	UCSR0C |= ((stopsize>>1)<<USBS0);

	//set frame size
	//UCSZn0:1 in UCSR0C, UCSR0C2 in UCSR0B
	if (framesize == 8)
	{
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	}
	else if (framesize == 7)
	{
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C |= (1<<UCSZ01);
		UCSR0C &= ~(1<<UCSZ00);
	}
	else if (framesize == 6)
	{
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C |= (1<<UCSZ00);
		UCSR0C &= ~(1<<UCSZ01);
	}
	else if (framesize == 5)
	{
		UCSR0B |= ~(1<<UCSZ02);
		UCSR0C |= ~((1<<UCSZ01)|(1<<UCSZ00));
	}
	else if (framesize == 9)
	{
		UCSR0B |= (1<<UCSZ02);
		UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	}
	

	//set baudrate in UBRRx
	//load 4 most significant bits in High
	//load 8 least significant bits in Low
	long ubrrval = UBRR_async_normal(rate);
	UBRR0H = (unsigned char)(ubrrval>>8);
	UBRR0L = (unsigned char)(ubrrval & 0xFF);

	//enable rx and tx
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

void enable_usart_rx_isr(void)
{
	UCSR0B |= (1<<RXCIE0);
}                                
                                 
void disable_usart_rx_isr(void)
{
	UCSR0B &= ~(1<<RXCIE0);
}

void uart_putchar(unsigned char c)
{
	while (!(UCSR0A & (1<<UDRE0)))
		{;}
	UDR0 = c;
}

void uart_putstr(char *str)
{
	while (*str)
		uart_putchar(*str++);
}

void uart_putnstr(char *str, unsigned char n)
{
	unsigned char i = 0;
	while (*str && n < i-1)
		uart_putchar(*str++);
}

void uart_puthex(unsigned char c)
{
	// upper for bits of a 8bit binary number is actually
	// a first character of hex representation
	// second character is 4 least significant bits
	// 'A' == 65 == 0100 0001 == 0x41
	unsigned char c1 = ((c & 0xF0) >> 4);
	unsigned char c2 = (c & 0x0F);

	// if n > 9, convert to a alphabetical character,
	// otherwise convert to a numerical character
	c1 += c1 > 9 ? 55 : '0';
	c2 += c2 > 9 ? 55 : '0';
	uart_putchar(c1);
	uart_putchar(c2);
}

//recursion my ass
void	uart_putnbr(signed long long nb)
{
	signed long long n;

	n = nb;
	if (n < 0)
	{
		uart_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		uart_putnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
	{
		uart_putchar(n + 48);
	}
}
//rx
unsigned char uart_getchar(void)
{
	while(!(UCSR0A & (1<<RXC0)))
		{;}
	return UDR0;
}
void uart_getline(char *buf, unsigned char size)
{
	unsigned char c;
	unsigned char i = 0;
	for (c = uart_getchar(); c != '\n' && i < size; c = uart_getchar())
		buf[i++] = c;
	buf[i] = '\0';
}

