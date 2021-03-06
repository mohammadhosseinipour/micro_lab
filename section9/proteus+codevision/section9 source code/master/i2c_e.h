#ifndef _i2c_e_INCLUDED_
#define _i2c_e_INCLUDED_

#define I2C_7BIT_DEVICE_ADDRESS 0x50
#define EEPROM_BUS_ADDRESS (I2C_7BIT_DEVICE_ADDRESS << 1)

void i2c_init(void);
unsigned char i2c_start(void);
void i2c_stop(void);
unsigned char i2c_read(unsigned char ack);
unsigned char i2c_write(unsigned char data);



void eeprom_write(unsigned int address, unsigned char data);
void eeprom_write_frame(unsigned int address,  char *data,char num ); 
void eeprom_write_pic(unsigned int address );

unsigned char eeprom_read(unsigned int address);
unsigned char eeprom_read_frame(unsigned int address,int num) ;

void i2c_24lc32(void);            //write
void i2c_24lc32_frame(void);     //write

void i2c_24lc32_read_frame(void); 
void i2c_24lc32_read_byte(void);
void i2c_24lc32_read_byte2(void); 


#endif

