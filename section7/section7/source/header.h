#ifndef _header_INCLUDED_
#define _header_INCLUDED_

#include <mega16.h>
#include <stdio.h>
#include <math.h>

// Alphanumeric LCD functions
#include <alcd.h>

extern int flag;
#define u_off 0
#define u_none_interrupt 1
#define u_interrupt 2
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)

// USART Receiver buffer
#define RX_BUFFER_SIZE 16
extern char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE <= 256
extern unsigned char rx_wr_index,rx_rd_index;
#else
extern unsigned int rx_wr_index,rx_rd_index;
#endif

#if RX_BUFFER_SIZE < 256
extern unsigned char rx_counter;
#else
extern unsigned int rx_counter;
#endif

// This flag is set on USART Receiver buffer overflow
extern bit rx_buffer_overflow;

// USART Receiver interrupt service routine

// Get a character from the USART Receiver buffer

#define TX_BUFFER_SIZE 16
extern char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE <= 256
extern unsigned char tx_wr_index,tx_rd_index;
#else
extern unsigned int tx_wr_index,tx_rd_index;
#endif

#if TX_BUFFER_SIZE < 256
extern unsigned char tx_counter;
#else
extern unsigned int tx_counter;
#endif
// Write a character to the USART Transmitter buffer

interrupt [USART_RXC] void usart_rx_isr(void);
char getchar(void);
interrupt [USART_TXC] void usart_tx_isr(void);
void putchar(char c);
void sub1(int rx_status,int tx_status, int baudrate);
void sub2();
void sub3();
void sub4();
void all_init();

#endif
