/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 11/29/2020
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

void main(void)
{
port_timer_lcd_init();

sub1_sub3_init();
sub1();
sub2_init();
flag=1;     ////////intialize_sub3/////////

while (1)
      {
      // Place your code here

      }
}
