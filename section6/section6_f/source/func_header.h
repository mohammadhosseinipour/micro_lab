#ifndef _func_header_INCLUDED_
#define _func_header_INCLUDED_

#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 7
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))
extern char buffer[50];
extern int flag;
extern unsigned int adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];

void port_timer_lcd_init();
void sub1_sub3_init();
void sub2_init();
unsigned int read_adc(unsigned char adc_input);
void sub1();
void sub2(unsigned char i,unsigned int new);
interrupt [ADC_INT] void adc_isr(void);



#endif
