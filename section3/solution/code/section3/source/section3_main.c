/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 10/18/2020
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


#include <section3_init.h>


char buffer[60];

char keypad[4][4]=
{
'0','1','2','3',
'4','5','6','7',
'8','9','A','B',
'c','D','E','F'};



// Declare your global variables here

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
int coll,row,column;
while(1){
    PORTB=0b00010000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=0;
    break;
    }

    PORTB=0b00100000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=1;
    break;
    }

    PORTB=0b01000000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=2;
    break;
    }

    PORTB=0b10000000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=3;
    break;
    }
}


if(coll==0b11110001)
{
column=0;
}
else if(coll==0b11110010)
{
column=1;
}
else if(coll==0b11110100)
{
column=2;
}

else if(coll==0b11111000)
{
column=3;
}

lcd_clear();
lcd_gotoxy(0,0);
lcd_putchar(keypad[row][column]);
delay_ms(1000);
//lcd_clear();
lcd_gotoxy(0,0);

}


void sub1()
{
lcd_init(16);
lcd_gotoxy(0,0);
 lcd_putsf("Mohammad");
 lcd_gotoxy(0,1);
 lcd_putsf("9626583");
}

void sub2()
{
int i;
lcd_clear();
lcd_gotoxy(0,0);
sprintf(buffer,"Welcome to the online lab classes due to Corona disease.");
for(i=0;i<60;i++)
{
lcd_puts(&buffer[i]);
delay_ms(250);
lcd_clear();
lcd_gotoxy(0,0);
}

}


void sub3(){
int coll,row,column;
while(1){
    PORTB=0b00010000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=0;
    break;
    }

    PORTB=0b00100000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=1;
    break;
    }

    PORTB=0b01000000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=2;
    break;
    }

    PORTB=0b10000000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=3;
    break;
    }
}


if(coll==0b11110001)
{
column=0;
}
else if(coll==0b11110010)
{
column=1;
}
else if(coll==0b11110100)
{
column=2;
}

else if(coll==0b11111000)
{
column=3;
}

lcd_clear();
lcd_gotoxy(0,0);
lcd_putchar(keypad[row][column]);
delay_ms(1000);
//lcd_clear();
lcd_gotoxy(0,0);


}

void sub4(){
 #asm("sei");
while(1){
    PORTB=0b11110000;
    //break; //optional but because of puting all these subs in one order i used break so i can continue others
}

}

char sub5_5()
{
  int coll,row,column;
while(1){
    PORTB=0b00010000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=0;
    break;
    }

    PORTB=0b00100000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=1;
    break;
    }

    PORTB=0b01000000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=2;
    break;
    }

    PORTB=0b10000000;
    #asm("NOP");
    coll=(PINB |0b11110000);
    if(coll!=0b11110000)
    {
    row=3;
    break;
    }
}


if(coll==0b11110001)
{
column=0;
}
else if(coll==0b11110010)
{
column=1;
}
else if(coll==0b11110100)
{
column=2;
}

else if(coll==0b11111000)
{
column=3;
}

return keypad[row][column];
}

void sub5(){
char a,b;
while(1)
{

    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_putsf("speed=");
    a=sub5_5();
    delay_ms(1000);
    b=sub5_5();
    lcd_gotoxy(6,0);
    if((a>=48&a<=52)&(b>=48&b<=57))
    {
    lcd_putchar(a);
    lcd_gotoxy(7,0);
    lcd_putchar(b);
    break;
    }
    else
    {
    lcd_putsf("EE");
    delay_ms(1000);
    }

}
 delay_ms(5000);

while(1)
{

    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_putsf("Time=");
    a=sub5_5();
    delay_ms(1000);
    b=sub5_5();
    lcd_gotoxy(6,0);
    if((a>=48&a<=57)&(b>=48&b<=57))
    {
    lcd_putchar(a);
    lcd_gotoxy(7,0);
    lcd_putchar(b);
    break;
    }
    else
    {
    lcd_putsf("EE");
    delay_ms(1000);
    }

}

delay_ms(5000);
while(1)
{

    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_putsf("Weigt=");
    a=sub5_5();
    delay_ms(1000);
    b=sub5_5();
    lcd_gotoxy(6,0);
    if((a>=48&a<=57)&(b>=48&b<=57))
    {
    lcd_putchar(a);
    lcd_gotoxy(7,0);
    lcd_putchar(b);
    break;
    }
    else
    {
    lcd_putsf("EE");
    delay_ms(1000);
    }

}
    delay_ms(5000);
while(1)
{

    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_putsf("Temp=");
    a=sub5_5();
    delay_ms(1000);
    b=sub5_5();
    lcd_gotoxy(6,0);
    if((a>=50&a<=55)&(b>=48&b<=57))
    {
    lcd_putchar(a);
    lcd_gotoxy(7,0);
    lcd_putchar(b);
    break;
    }
    else
    {
    lcd_putsf("EE");
    delay_ms(1000);
    }

}

  delay_ms(5000);

}



void main(void)
{
init_all1();
// Declare your local variables here


// Global enable interrupts
sub1();
sub2();
sub3();
sub5();
sub4();
}
