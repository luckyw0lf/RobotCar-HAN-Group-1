//GPL-3.0-only
#ifndef ANALOG_H_
 #define ANALOG_H_

//init adc with *prescaler* value
//if prescaler value passed is incorrect,
//default value for prescaler is2
void adc_init(unsigned char prescaler);

//init prescaler in Free-running mode
//adc_result value will be updated in ISR(ADC_vect)

void adc_init_free(void);
#ifndef FREE_ADC_ISR
 #warning "FREE_ADC_ISR is not defined, adc_init_free() has no effect"
#endif

void adc_start(void);

void adc_wait(void);

void adc_start_and_wait(void);

void tempsensor_init(void);
signed int tempsensor_result(signed int offset);
#endif // ANALOG_H_
