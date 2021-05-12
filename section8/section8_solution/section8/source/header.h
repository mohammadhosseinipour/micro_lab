#ifndef _header_INCLUDED_
#define _header_INCLUDED_

#include <mega16.h>
#include <delay.h>
#include <math.h>
// Graphic Display functions
#include <glcd.h>

// Font used for displaying text
// on the graphic display
#include <font5x7.h>

extern const unsigned short sec816x8[];
extern flash unsigned char pic[];
void sub1();
void init_all();
void sub2();
void clock_maker(int h,int m,int s);
void sub3();

#endif