/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 10/2/2020
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

#include <mega16.h>
#include <delay.h>

// Declare your global variables here
flash unsigned char digit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//flash unsigned char digit[] = {0x6F,0x7F, 0x07, 0x7D, 0x6D,  0x66, 0x4F, 0x5B, 0x06,0x3F};
void show1(int a1,int a2)
{
      PORTD&=~(0b00001010);  //7seg2 on,green light off
      PORTD|= (0b00000101);   //7seg1 off,red light on
      PORTC=digit[a1];
      delay_ms(50);
      PORTD&=~(0b00001001);  //7seg1 on,green light off
      PORTD|= (0b00000110);  //7seg2 off,red light on
      PORTC=digit[a2];
      delay_ms(50);
}

void show2(int b1,int b2)
{
      PORTB&=~(0b00001010); //7seg2 on,green light off
      PORTB|= (0b00000101); //7seg1 off,red light on
      PORTA=digit[b1];
      delay_ms(50);
      PORTB&=~(0b00001001); //7seg1 on,green light off
      PORTB|= (0b00000110); //7seg2 off,red light on
      PORTA=digit[b2];
      delay_ms(50);
}

void main(void)
{
int A,a1,a2,b1,b2;
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (1<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (1<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

A=30;
while (1)
    {
      a1=A%10;
      a2=(A/10)%10;
      show1(a1,a2);
      A-=1;
      while((PIND&0b00100000)==0b00100000)
        {
         //wait
            show1(a1,a2);
        }

      if((PIND&0b00010000)==0b00010000||A==0)
      {
        PORTD|=(0b00001011);//seven seg off,green light on
        PORTD&=~(0b00000100);//red light off
        A=30;
        while(1)
        {
        b1=A%10;
        b2=(A/10)%10;
        show2(b1,b2);
        A-=1;
        while((PINB&0b00100000)==0b00100000)
            {
                //wait
                show2(b1,b2);
            }
        if((PINB&0b00010000)==0b00010000||A==0)
            {
            PORTB|=(0b00001011);//seven seg off,green light on
            PORTB&=~(0b00000100);//red light off
            break;
            }

        }
        A=30;
      }

    }
}