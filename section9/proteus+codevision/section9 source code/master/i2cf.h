#ifndef _i2cf_INCLUDED_
#define _i2cf_INCLUDED_

#define I2C_7BIT_DEVICE_ADDRESS 0x50
#define EEPROM_BUS_ADDRESS (I2C_7BIT_DEVICE_ADDRESS << 1)


void eeprom_write(unsigned int address, unsigned char data);
void eeprom_write_frame(unsigned int address,  char *data,char num ); 
void eeprom_write_pic(unsigned int address );

unsigned char eeprom_read(unsigned int address);
unsigned char eeprom_read_frame(unsigned int address,int num) ;
void i2c_24lc32_read_byte2(void);

void i2c_24lc32_read_frame(void); 
void i2c_24lc32_read_byte(void); 
void i2c_24lc32(void); 
void i2c_24lc32_frame(void); 

//char I2C_Slave_Receive(void);
//char I2C_Slave_Transmit(char data);
//char I2C_Slave_Listen(void);
//void I2C_Slave_Init(char slave_address);





#endif

