#ifndef _myheader_INCLUDED_
#define _myheader_INCLUDED_


#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#include <adcf.h>
#include <spif.h>
#include <portf.h>
#include <twi.h>
#include <mandala2.h>
#include <glcd.h>
#include <font5x7.h>
#include <i2c.h>
#include <i2cf.h>
#include <stdlib.h>
#include <uartf.h>
#include <glcdf.h>
#include "I2C_Slave_H_file.h"


// Declare your global variables here

extern volatile eeprom char data_rec[512];
extern bit master_micro;

#endif
