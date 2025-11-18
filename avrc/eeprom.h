//GPL-3.0-only
void eeprom_write(unsigned int address, unsigned char data);

//write to eeprom starting from most significant bits(recommended)
void eeprom_write_long_msb(unsigned int address, unsigned long data);

//write to eeprom starting from least significant bits
void eeprom_write_long_lsb(unsigned int address, unsigned long data);

unsigned char eeprom_read(unsigned int address);

//read data and write them to address pointed to by p
// when writing to int* typecast is needed
//eeprom_read_long_pointer(address, (long *)&p, sizeof(p));
void eeprom_read_long_pointer(unsigned int address, long *p, unsigned char size);

//eeprom_read_long() takes address, pointer to a buffer and an index value bufsize
//and read at most bufsize of data from eeprom address to a *buf
void eeprom_read_long(unsigned int address, char *buf, unsigned char bufsize);
