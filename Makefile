toycar-uart-control:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/toycar-uart-control.c avrc/toycar.h avrc/toycar.c  avrc/pwm.h avrc/pwm.c  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h -o /tmp/toycar-uart-control.out
	avr-objcopy -I elf32-avr -O ihex /tmp/toycar-uart-control.out toycar-uart-control.hex
	rm /tmp/toycar-uart-control.out
toycar-uart-control-S:
	avr-gcc -S -mmcu=atmega328p -O2 -std=c99 examples/toycar-uart-control.c avrc/toycar.h avrc/toycar.c avrc/millis.c avrc/pwm.h avrc/pwm.c avrc/millis.h  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h 
toycar-uart-control-E:
	avr-gcc -E -mmcu=atmega328p -O2 -std=c99 examples/toycar-uart-control.c avrc/toycar.h avrc/toycar.c avrc/millis.c avrc/pwm.h avrc/pwm.c avrc/millis.h  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h 

toycar-ultrasonic:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/toycar-ultrasonic.c avrc/hcsr04.c avrc/hcsr04.h avrc/toycar.h avrc/millis.c avrc/millis.h avrc/toycar.c  avrc/pwm.h avrc/pwm.c  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h -o /tmp/toycar-ultrasonic.out
	avr-objcopy -I elf32-avr -O ihex /tmp/toycar-ultrasonic.out toycar-ultrasonic.hex
	rm /tmp/toycar-ultrasonic.out
toycar-ultrasonic-S:
	avr-gcc -S -mmcu=atmega328p -O2 -std=c99 examples/toycar-ultrasonic.c avrc/hcsr04.h avrc/hcsr04.c avrc/toycar.h avrc/millis.c avrc/millis.h avrc/toycar.c avrc/millis.c avrc/pwm.h avrc/pwm.c avrc/millis.h  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h 
toycar-ultrasonic-E:
	avr-gcc -E -mmcu=atmega328p -O2 -std=c99 examples/toycar-ultrasonic.c avrc/hcsr04.h avrc/hcsr04.c avrc/toycar.h avrc/millis.c avrc/millis.h avrc/toycar.c avrc/millis.c avrc/pwm.h avrc/pwm.c avrc/millis.h  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h 

