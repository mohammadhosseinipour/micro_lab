#include <header.h>
 int flag=3;


// USART Receiver buffer
char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE <= 256
unsigned char rx_wr_index=0,rx_rd_index=0;
#else
unsigned int rx_wr_index=0,rx_rd_index=0;
#endif

#if RX_BUFFER_SIZE < 256
unsigned char rx_counter=0;
#else
unsigned int rx_counter=0;
#endif

// This flag is set on USART Receiver buffer overflow
bit rx_buffer_overflow;

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{
char status,data;
status=UCSRA;
data=UDR;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer[rx_wr_index++]=data;
#if RX_BUFFER_SIZE == 256
   // special case for receiver buffer size=256
   if (++rx_counter == 0) rx_buffer_overflow=1;
#else
   if (rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
   if (++rx_counter == RX_BUFFER_SIZE)
      {
      rx_counter=0;
      rx_buffer_overflow=1;
      }
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter==0);
data=rx_buffer[rx_rd_index++];
#if RX_BUFFER_SIZE != 256
if (rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
#endif
#asm("cli")
--rx_counter;
#asm("sei")
return data;
}
#pragma used-
#endif

// USART Transmitter buffer
char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE <= 256
unsigned char tx_wr_index=0,tx_rd_index=0;
#else
unsigned int tx_wr_index=0,tx_rd_index=0;
#endif

#if TX_BUFFER_SIZE < 256
unsigned char tx_counter=0;
#else
unsigned int tx_counter=0;
#endif

// USART Transmitter interrupt service routine
interrupt [USART_TXC] void usart_tx_isr(void)
{
if (tx_counter)
   {
   --tx_counter;
   UDR=tx_buffer[tx_rd_index++];
#if TX_BUFFER_SIZE != 256
   if (tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
while (tx_counter == TX_BUFFER_SIZE);
#asm("cli")
if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer[tx_wr_index++]=c;
#if TX_BUFFER_SIZE != 256
   if (tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
#endif
   ++tx_counter;
   }
else
   UDR=c;
#asm("sei")
}
#pragma used-
#endif

// Standard Input/Output functions





void sub1(int rx_status,int tx_status, int baudrate)
{
    int x;
    x=floor(500000/baudrate)-1;
    UBRRH=x/256;
    UBRRL=x%256;
    switch(rx_status)
    {
        case 0:
        UCSRB|=(0<<RXCIE)| (0<<RXEN);
        break;
        case 1:
        UCSRB|=(0<<RXCIE)| (1<<RXEN);
        break;
        case 2:
        UCSRB|=(1<<RXCIE)| (1<<RXEN);
        break;
        default: break;
    }
    switch(tx_status)
    {
        case 0:
        UCSRB|=(0<<TXCIE)| (0<<TXEN);
        break;
        case 1:
        UCSRB|=(0<<TXCIE)| (1<<TXEN);
        break;
        case 2:
        UCSRB|=(1<<TXCIE)| (1<<TXEN);
        break;
        default: break;
    }
}


void sub2()
{
// i assumed # means that the text finished
char a='0';
char buff[20];
int i;
int char_count=0;
printf("Part2 Beggins,put# at end of string: \r\n");
sub1(u_none_interrupt,u_none_interrupt,9600);
buff[char_count]='(';
while(a!='#')
{
    if(char_count==19)
         break;
    a=getchar();
    buff[char_count+1]=a;
    char_count+=1;

}
buff[char_count]=')';
for(i=0;i<=char_count;i++)
    putchar(buff[i]);

printf("Part2 Ends. \r\n");

}

void sub3()
{

    int i=0,j;
    char a;
    char buffer[60];
    if(flag==3){
    printf("Part3 Beggins: \r\n");
    sub1(u_interrupt,u_none_interrupt,9600);
    while(i<4)
    {
        i++;
        a=getchar();
        if (a>='0' && a<='9')
        {
            putchar(a);
            putchar('0');
            printf("\r\n");
        }
        else if(a=='D')
        {
            lcd_clear();
            sprintf(buffer,"lcd delete ");
            lcd_gotoxy(0,0);
            lcd_puts(&buffer[0]);
        }
        else if(a=='H')
        {
            putchar('n');
            putchar('o');
            putchar('t');
            putchar('h');
            putchar('i');
            putchar('n');
            putchar('g');
        }
        else
        {
            sprintf(buffer,"no function");
            for(j=0;j<11;j++)
                putchar(buffer[j]);
        }
        printf("\r\n");

    }
    printf("Part3 Ends. \r\n");
    flag=4;
    }

}

void sub4()
{
char a;
int j,count=0,f=1;
char buff1[28],buff2[17],buff3[24];
sprintf(buff1,"Length of frame not correct");
sprintf(buff2,"Frame is correct");
sprintf(buff3,"Frame must be 5 integer");
if(flag==4)
{
        sub1(u_interrupt,u_interrupt,9600);
        printf("Part4 Beggins: \r\n");
        while(1)
        {
        a=getchar();
        while(a!='(')
        {
            for(j=0;j<27;j++)
                putchar(buff1[j]);
            printf("\r\n");
            a=getchar();
        }
        while(1)
        {
            a=getchar();
            if(a==')')
                break;
            if(a<='0'||a>='9')
                f=0;
            count++;
        }
        if(count<5)
        {
            for(j=0;j<28;j++)
                putchar(buff1[j]);
        }
        else if(count==5 && f==1)
        {
             for(j=0;j<17;j++)
                putchar(buff2[j]);
        }
        else
        {
             for(j=0;j<24;j++)
                putchar(buff3[j]);
        }
        printf("\r\n");
        f=1;
        count=0;
        }
        printf("Part3 Ends. \r\n");
}
}
void all_init()
{
     // Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=In
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (1<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=T
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(1<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")
}