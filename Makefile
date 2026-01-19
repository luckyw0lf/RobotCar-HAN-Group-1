main:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 main.c avrc/hcsr04.c avrc/hcsr04.h avrc/toycar.h avrc/millis.c avrc/millis.h avrc/toycar.c  avrc/pwm.h avrc/pwm.c  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h -o /tmp/main.out
	avr-objcopy -I elf32-avr -O ihex /tmp/main.out main.hex
# 	rm /tmp/main.out

toycar-uart-control:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/toycar-uart-control.c avrc/toycar.h avrc/toycar.c  avrc/pwm.h avrc/pwm.c  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h -o /tmp/toycar-uart-control.out
	avr-objcopy -I elf32-avr -O ihex /tmp/toycar-uart-control.out toycar-uart-control.hex
	rm /tmp/toycar-uart-control.out

toycar-ultrasonic:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/toycar-ultrasonic.c avrc/hcsr04.c avrc/hcsr04.h avrc/toycar.h avrc/millis.c avrc/millis.h avrc/toycar.c  avrc/pwm.h avrc/pwm.c  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h -o /tmp/toycar-ultrasonic.out
	avr-objcopy -I elf32-avr -O ihex /tmp/toycar-ultrasonic.out toycar-ultrasonic.hex
	rm /tmp/toycar-ultrasonic.out
toycar-ir:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/toycar-ir.c avrc/hcsr04.c avrc/hcsr04.h avrc/toycar.h avrc/millis.c avrc/millis.h avrc/toycar.c  avrc/pwm.h avrc/pwm.c  avrc/analog.c avrc/analog.h avrc/uart.c avrc/uart.h -o /tmp/toycar-ir.out
	avr-objcopy -I elf32-avr -O ihex /tmp/toycar-ir.out toycar-ir.hex
	rm /tmp/toycar-ir.out
test-ultrasonic:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/test-ultrasonic.c avrc/hcsr04.c avrc/hcsr04.h avrc/toycar.h avrc/toycar.c avrc/pwm.h avrc/pwm.c avrc/uart.c avrc/uart.h -o /tmp/test-ultrasonic.out
	avr-objcopy -I elf32-avr -O ihex /tmp/test-ultrasonic.out test-ultrasonic.hex
	rm /tmp/test-ultrasonic.out
jumptable-ultrasonic:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/jumptable-ultrasonic.c avrc/hcsr04.h avrc/hcsr04.c avrc/pwm.h avrc/pwm.c avrc/uart.c avrc/uart.h -o /tmp/jumptable-ultrasonic.out
	avr-objcopy -I elf32-avr -O ihex /tmp/jumptable-ultrasonic.out jumptable-ultrasonic.hex
	rm /tmp/jumptable-ultrasonic.out

test-button:
	avr-gcc -mmcu=atmega328p -O2 -std=c99 examples/test-button.c avrc/pwm.h avrc/millis.h avrc/millis.c avrc/button.c avrc/button.h avrc/pwm.c avrc/uart.c avrc/uart.h -o /tmp/button.out
	avr-objcopy -I elf32-avr -O ihex /tmp/button.out button.hex
# 	rm /tmp/button.out
