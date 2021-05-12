#include<header.h>

 int flag=0,hour=0,min=0,sec=0,count=1000;
char buffer[60];


// Declare your global variables here

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
flag=1;

}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
if(flag==1)
{
    flag=0;
}
else if(flag==0)
{
    hour=0;
    min=0;
    sec=0;
    lcd_gotoxy(0,0);
    sprintf(buffer,"%d:%d:%d   ",hour,min,sec);
    lcd_puts(&buffer[0]);
}

}

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
    if((PINB|0b11110111)==0b11110111)
    {
        if(count==0)
        {
            lcd_gotoxy(0,1);
            lcd_putsf("FULL  ");
        }
        else
        {
            count--;
            lcd_gotoxy(0,1);
            sprintf(buffer,"%d   ",count);
            lcd_puts(&buffer[0]);
        }
    }
    else if((PINB|0b11101111)==0b11101111)
    {
     count++;
     if(count==1001)
     {
      count=1000;
     }
     lcd_gotoxy(0,1);
     sprintf(buffer,"%d   ",count);
     lcd_puts(&buffer[0]);
    }


}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Reinitialize Timer 0 value
TCNT0=0xB0;
if(flag==1)
{
    if(sec==59)
    {
        if(min==59)
        {
            if(hour==23)
            {
                hour=0;
            }
            else
            {
                hour++;
            }
            min=0;
        }
        else
        {
            min++;
        }
        sec=0;

    }
    else
    {
        sec++;
    }
    lcd_gotoxy(0,0);
    sprintf(buffer,"%d:%d:%d",hour,min,sec);
    lcd_puts(&buffer[0]);

}

}


