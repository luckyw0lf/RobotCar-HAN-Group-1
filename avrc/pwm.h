//GPL-3.0-only
#ifndef PWM_H_
 #define PWM_H_

//pwm_ICRn_val() calculates ICRn value
//can be used to calculate duty value
//(assuming desired duty value is 10%, PWM frequency 50Hz and prescaler 128)
//duty10 = ((pwm_ICRn_val(F_CPU, 50, 128))/10)
unsigned int pwm_ICRn_val(unsigned long f_cpu, unsigned long f_pwm, unsigned int prescaler);

//init_fastpwm_icr1() will configure Timer1 for fastpwm mode with TOP in ICR1
//reffer to a datasheet for available prescaler values
//default value for prescaler on TIMER1 is 1
//
//NOTE: this function will NOT set ICR1 and OCR1, set them manually
//with set_top_in_icr1() and set_duty_ocr1A()
void init_fastpwm_icr1(unsigned int prescaler);

//set_top_in_icr1() expets a value that will be written to ICR1 register
//use pwm_ICRn_val function to get ICR1 value
//(assuming desired PWM frequency is 50Hz, prescaler is 128)
//
//set_top_in_icr1(pwm_ICRn_val(F_CPU, 50, 128))
void set_top_in_icr1(unsigned int pwm_ICRn_value);

//fastpwm signal on channel A (PB1)
//
//set_duty_ocr1A(pwm_ICRn_val(...))
void set_duty_ocr1A(unsigned int duty);
//fastpwm signal on channel B (PB2)
void set_duty_ocr1B(unsigned int duty);
//fastpwm signal on channels A and B
void set_duty_ocr1AB(unsigned int duty);

//inverted mode
void set_duty_inverted_ocr1A(unsigned int duty);
void set_duty_inverted_ocr1B(unsigned int duty);
void set_duty_inverted_ocr1AB(unsigned int duty);
#endif // PWM_H_
