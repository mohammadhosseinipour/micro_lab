/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 10/1/2020
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


#define F_CPU 1000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <mega16.h>
//#include <avr/io.h>		/* Include AVR std. library file */
#include <stdio.h>		/* Include std. library file */
#include <stdlib.h>
//#include <time.h>
#include <delay.h>
#include <math.h>

int sevseg[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
void sub1()
{
    int i;
    PORTB=0x00;
    for(i=0;i<8;i++)
    {
        PORTB ^=0xff;
        delay_ms(500);
    }
}

void sub2()
{
    int a=0b00000001;
    int i;
    for(i=0;i<8;i++)
    {
    PORTB=a;
    a=a<<1;
    delay_ms(375);

    }
    PORTB=0x00;
}

/* sub3 shows every PINA changes on LEDS for 3 seconds. i added 3 seconds because of loop of all these sub problems. */
void sub3()
{
    int i=0;
    for(i=0;i<300;i++)
    {
        delay_ms(10);
        PORTB=PINA;
    }
}

void sub4()
{
    int i;
    PORTD=0x00;
    for(i=9;i>=0;i--)
    {
        PORTC=sevseg[i];
        delay_ms(500);
    }


}
void sub5()
{
    int  num, decimal_val = 0, base = 1, rem,i;
    int firstseg,secondseg,thirdseg,fourthseg;
    int ournum=decimal_val;
    num=PINA;
    //this while calculates deciimal number
    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;
    }
    ournum=decimal_val;
    while(ournum>0)
    {
        firstseg=0;
        secondseg=ournum%10;
        thirdseg=(ournum/10)%10;
        fourthseg=(ournum/100)%10;
        for(i=5;i>0;i--)
        {
        PORTD=0b00000111;
        PORTC=sevseg[(2*i)%10];
        delay_ms(100);

        PORTD=0b00001011;
        PORTC=sevseg[secondseg]|0b10000000;  /*0b10000000 is for dot*/
        delay_ms(100);

        PORTD=0b00001101;
        PORTC=sevseg[thirdseg];
        delay_ms(100);

        PORTD=0b00001110;
        PORTC=sevseg[fourthseg];
        delay_ms(100);
        }
        ournum-=1;
    }
}

void sub6()
{   while(1)
    {
    if((PIND&0b00010000)==0b0)
    {
    PORTD=(PORTD&0b11111110)|0b00001110;
    PORTC=sevseg[0];
    }
    else if((PIND&0b00100000)==0b0)
    {
    PORTD=(PORTD&0b11111101)|0b00001101;
    PORTC=sevseg[0];
    }
    else if((PIND&0b01000000)==0b0)
    {
    PORTD=(PORTD&0b11111011)|0b00001011;
    PORTC=sevseg[0];
    }
    else if ((PIND&0b10000000)==0b0)
    {
    PORTD=(PORTD&0b11110111)|0b00000111;
    PORTC=sevseg[0];
    }
    }
}

void sub7()
{
    sub1();
    sub2();
    sub4();
    while(1)
    {
    sub3();
    sub5();
    sub6();
    }

}


void main(void){
// Declare your global variables here


// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P
PORTA=(1<<PORTA7) | (1<<PORTA6) | (1<<PORTA5) | (1<<PORTA4) | (1<<PORTA3) | (1<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);

// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

    sub7();
}
