#ifndef _i2c_f_INCLUDED_
#define _i2c_f_INCLUDED_

#include <math.h>  

#define F_CPU 8000000UL                            /* Define CPU clock Frequency e.g. here its 8MHz */
                             /* Include math function */
#define SCL_CLK 100000L                            /* Define SCL clock frequency */
#define BITRATE(TWSR)    ((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */
#define Slave_Address        0x20
#define Slave_Write_Address 0x20
#define Slave_Read_Address  0x21
#define	count					10

void I2C_Init2();                                /* I2C initialize function */
char  I2C_Start2(char write_address);            /* I2C start function */
char  I2C_Repeated_Start(char read_address);    /* I2C repeated start function */
void I2C_Stop2();                                /* I2C stop function */
void I2C_Start_Wait(char write_address);        /* I2C start wait function */
char  I2C_Write2(char data);                    /* I2C write function */
char I2C_Read_Ack();                            /* I2C read ack function */
char I2C_Read_Nack();							/* I2C read nack function */


void I2C_Slave_Init(char slave_address);		/* I2C slave initialize function with Slave address */
char I2C_Slave_Listen();						/* I2C slave listen function */
char I2C_Slave_Transmit(char data);			/* I2C slave transmit function */
char I2C_Slave_Receive();						/* I2C slave receive function */


#endif

