#ifndef _glcd_s_INCLUDED_
#define _glcd_s_INCLUDED_

#define x_center_clock   32
#define y_center_clock   32
#define sec_radius       19
#define min_radius       15
#define hour_radius       12


void glcd_init_func(void);

void clock_display(void);

void deleteclock(char data,char xxold,char yyold);


#endif

