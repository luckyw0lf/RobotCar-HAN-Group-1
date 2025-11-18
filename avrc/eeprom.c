//GPL-3.0-only

#define __AVR_ATmega328P__

#include <util/atomic.h>
#include <avr/io.h>

void eeprom_write(unsigned int address, unsigned char data)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//wait for completion of previous write
		while (EECR & (1<<EEPE))
			{;}

		EEAR = address;
		EEDR = data;
		EECR |= (1<<EEMPE);
		EECR |= (1<<EEPE);
	}
}

void eeprom_write_long_msb(unsigned int address, unsigned long data)
{
	//data = 1010 1111 0000 1111
	//datasize = 2

	unsigned int datasize = sizeof(data);
	while (datasize > 0)
	{
		unsigned char datapiece = (unsigned char)(data>>((datasize-1)*8));
		eeprom_write(address, datapiece);
		address++;
		datasize--;
	}
}

void eeprom_write_long_lsb(unsigned int address, unsigned long data)
{

	unsigned int datasize = sizeof(data);
	unsigned int i = 0;
	while (datasize > i)
	{
		unsigned char datapiece = (unsigned char)(data>>(i*8));
		eeprom_write(address, datapiece);
		address++;
		i++;
	}
}
unsigned char eeprom_read(unsigned int address)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//wait for completion of previous write
		while (EECR & (1<<EEPE))
			{;}

		EEAR = address;
		EECR |= (1<<EERE);
		return (EEDR);
	}
}
void eeprom_read_long_pointer(unsigned int address, long *p, unsigned char size)
{
	// eeprom_read_long_pointer(address, (long *)&b, sizeof(char));
	while (size-- > 0)
	{
		*p |= (eeprom_read(address)<<(size*8));
		address++;
	}
}

void eeprom_read_long(unsigned int address, char *buf, unsigned char bufsize)
{
	unsigned char i = 0;
	while (bufsize > 0)
	{
		buf[i] = eeprom_read(address);
		i++;
		bufsize--;
	}
}
