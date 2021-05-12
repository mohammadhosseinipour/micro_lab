/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 11/8/2020
Author  :
Company :
Comments:


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <header.h>

// Declare your global variables here
char buffer[60];
int dor=0;
int i=0,flag=0;
int phase_sp=0;
// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Reinitialize Timer1 value
TCNT1H=0x85EE >> 8;
TCNT1L=0x85EE & 0xff;
// Place your code here

}

// Timer1 input capture interrupt service routine
interrupt [TIM1_CAPT] void timer1_capt_isr(void)
{
// Place your code here

}

// Timer2 output compare interrupt service routine
interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
lcd_clear();
//it needs 4 pulses for one rotate so speed=(1000/(4*65.26))*60=229.8
sprintf(buffer,"speed:%d.%d RPM",229,8);
lcd_puts(&buffer[0]);
i++;
    if(i<=100){
        i++;
        switch(phase_sp){
        case 0:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b00010000);
            phase_sp++;
            //delay_ms(1000);
            break;
        case 1:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b00100000);
            phase_sp++;
            //delay_ms(1000);
            break;
        case 2:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b01000000);
            phase_sp++;
            //delay_ms(1000);
            break;
        case 3:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b10000000);
            phase_sp=0;
            //dor++;
            //delay_ms(1000);
            break;
        }
        if(i==101)
        {
            delay_ms(1000);
        }
    }
    else if(i>100)
    {   i++;

        switch(phase_sp){
        case 3:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b00010000);
            phase_sp=0;
            //dor++;
            //delay_ms(1000);
            break;
        case 2:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b00100000);
            phase_sp++;
            //delay_ms(1000);
            break;
        case 1:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b01000000);
            phase_sp++;
            //delay_ms(1000);
            break;
        case 0:
            PORTB= PORTB &(0b00001111);
            PORTB= PORTB |(0b10000000);
            phase_sp++;
            //delay_ms(1000);
            break;
        }
        if(i==200)
        {
            i=0;
            delay_ms(1000);
        }
    }
}





void sub1()
{
//OCR0=0x1A;
//OCR0=0x4D;
//OCR0=0x80;
//OCR0=0xB2;
OCR0=0xE5;
delay_ms(5000);
}

// sub2 IS ON PDF FILE
// y=2.55*x+0.5


void sub3()
{
// 0 input means 5% dutycycle and 255 means 95%
// so the line given by these twe points will be
// IN y=ax+b => a=(95-5)/(255-0)=0.35  AND  b=5 so dutycycle = y = 0.35*x + 5
float y1,y2;
int w=0,i;
while(w<30)
{
    w++;
    i=PINA;
    y1=(i*0.35)+5;
    y2=(y1*2.55)+0.5;
    OCR0=(int)y2;
    lcd_clear();
    sprintf(buffer,"OCR0=%d",(int)y2);
    lcd_puts(&buffer[0]);
    delay_ms(1000);

}

lcd_clear();
}


void main(void)
{
init_all();
sub1();
sub3();
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
