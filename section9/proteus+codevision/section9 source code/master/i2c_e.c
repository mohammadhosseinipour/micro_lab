  #include <myheader.h>
  #include <i2c_e.h>
  #include <mandala2.h>

volatile eeprom char data_rec[512];
 
/* read a byte from the EEPROM */
unsigned char eeprom_read(unsigned int address) 
{
unsigned char data;
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 0);
/* send MSB of address */
i2c_write(address >> 8);
/* send LSB of address */
i2c_write((unsigned char) address);
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 1);
data=i2c_read(0);
i2c_stop();
return data;
}

/*********************************************/
/* read a byte from the EEPROM */
unsigned char eeprom_read_frame(unsigned int address,int num) 
{
int i,j;

unsigned char data;

if (address!=0)j=4;
else j=0;

i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 0);
/* send MSB of address */
i2c_write(address >> 8);
/* send LSB of address */
//i2c_write((unsigned char) address);
i2c_write( address&0x00ff);
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 1);
for(i=j;i<num;i++)
{
if(i==(num-1))data_rec[i]=i2c_read(0);
else data_rec[i]=i2c_read(1);
data=data_rec[i];
}
i2c_stop();
return data;
}
/*************************************/

/* write a byte to the EEPROM */
void eeprom_write(unsigned int address, unsigned char data) 
{
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 0);
/* send MSB of address */
i2c_write(address >> 8);
/* send LSB of address */
i2c_write((unsigned char) address);
i2c_write(data);
i2c_stop();
/* 10ms delay to complete the write operation */
delay_ms(10);
}


/* write a frame to the EEPROM */
void eeprom_write_frame(unsigned int address, char *data,char num ) 
{
char i;
char *ip;
ip=data;

i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 0);
/* send MSB of address */
i2c_write(address >> 8);
/* send LSB of address */
i2c_write((unsigned char) address);
for (i=0;i<num;i++)
{
i2c_write(*(ip+i));
}
i2c_stop();
/* 10ms delay to complete the write operation */
delay_ms(10);
}


void eeprom_write_pic(unsigned int address ) 
{
char i;



i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 0);
//I2C_Write2(EEPROM_BUS_ADDRESS | 0);

/* send MSB of address */
i2c_write(address >> 8);
/* send LSB of address */
i2c_write((unsigned char) address);
for (i=0;i<16;i++)
{
i2c_write(mandalapic[i+address]); 

}
i2c_stop();
/* 10ms delay to complete the write operation */
delay_ms(10);
}


void i2c_24lc32(void) 
{
unsigned char j;
 char data[]={1,2,3};

i2c_init();






/* write the byte 55h at address AAh */
eeprom_write(0xaa,data[0]);
eeprom_write(0xab,data[1]);
eeprom_write(0xac,data[2]);


/* read the byte from address AAh */
j=eeprom_read(0xaa);
j=eeprom_read(0xab);
j=eeprom_read(0xac);
}


void i2c_24lc32_frame(void) 
{
int i;
long int data2;


i2c_init();

for (i=0;i<64;i++)
{
data2=i*0x0010;
eeprom_write_pic(data2);
}
}


void i2c_24lc32_read_frame(void) 
{
 int i;
 char scr[20];

glcd_clear();
    
eeprom_read_frame(0,512);  //4  508       
glcd_putimagee(4,0,data_rec,GLCD_PUTCOPY);                     

eeprom_read_frame(516,512);          
glcd_putimagee(4,32,data_rec,GLCD_PUTCOPY);       
}


/*************************************/
void i2c_24lc32_read_byte(void) 
{
 char i;
 char data=0xff;
 char scr[20];
 for (i=0;i<1024;i++)
 {
 data=eeprom_read(i);
 if (data !=mandalapic[i])
  {
    sprintf(scr,"error [%d]=%d\r\n",i,data);
    puts(scr);
    
    } 
    }
    

}

void i2c_24lc32_read_byte2(void) 
{
 int i;
 char data=0xff;
 char scr[20];
 for (i=0;i<512;i++)
 {
 data_rec[i]=eeprom_read(i);
 if (data_rec[i] ==mandalapic[i])
  {
    sprintf(scr,"error [%d]=%d--%d\r\n",i,data_rec[i],mandalapic[i]);
    puts(scr);
    
    } 
    } 
     sprintf(scr,"data correct\r\n");
    puts(scr);   
    
 for (i=512;i<1024;i++)
 {
 data_rec[i]=eeprom_read(i+512);
 if (data_rec[i] ==mandalapic[i+512])
  {
    sprintf(scr,"error [%d]=%d--%d\r\n",i,data_rec[i],mandalapic[i+512]);
    puts(scr);
    
    } 
    }
    
      sprintf(scr,"data correct\r\n");
    puts(scr);   
}



/*
Programming steps in the master device

    Initialize I2C.
    Generate START condition.
    Write device Write address (SLA+W) and check for acknowledgement.
    After acknowledgement write data to slave device.
    Generate REPEATED START condition with SLA+R.
    Receive data from slave device.


Programming steps in slave device

    Initialize I2C with slave device address.
    Listen to bus for get addressed by master.
    While addressed with SLA+W by master device, receive data from master device.
    Return acknowledgement after each byte received.
    Clear interrupt flag after REPEATED START/STOP received.
    Print received data on LCD.
    Again listen to bus for get addressed by master.
    While addressed with SLA+R by master device, transmit data to master device.
    Transmit data till NACK/REPEATED START/STOP receive from master.
    Clear interrupt flag after NACK/REPEATED START/STOP received.
    
    
    https://www.avrfreaks.net/forum/twi-module-seems-buggy-multi-master-communications
*/


