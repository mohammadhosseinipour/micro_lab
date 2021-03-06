
#include <myheader.h>


flash int cos6data[]={0    ,  11    ,21    ,  31    ,  41    ,50    ,  59    ,  67    ,  74    ,81    ,87    ,
91    ,95    ,  98    ,  99    ,  100    ,99    ,98    ,  95    ,  91    ,87    ,81    ,74    ,67    ,59    ,50    ,41    ,
31    ,21    ,  11    ,0    ,  -10    ,-21    ,  -31    ,  -41    ,-50    ,-59    ,-67    ,-74    ,
-81    ,-87    ,-91    ,-95    ,-98    ,-99    ,-100    ,  -99    ,-98    ,-95    ,
-91    ,-87    ,-81    ,-74    ,-67    ,-59    ,-50    ,-41    ,-31    ,-21    ,-11    ,
0    
};

flash int sin6data[]={
100    ,99    ,98    ,95    ,91    ,87    ,81    ,74    ,
67    ,59    ,  50    ,41    ,31    ,21    ,  10    ,0    ,
-10    ,-21    ,-31    ,-41    ,-50    ,-59    ,-67    ,-74    ,
-81    ,-87    ,-91    ,-95    ,-98    ,-99    ,-100    ,-99    ,
-98    ,-95    ,-91    ,  -87    ,-81    ,-74    ,-67    ,  -59    ,
-50    ,  -41    ,-31    ,  -21    ,-11    ,  0    ,10    ,  21    ,
31    ,  41    ,50    ,  59    ,      67    ,  74    ,  81    ,    86    ,
91    ,  95    ,98    ,  99    ,100    
};

char hx[]={0,6,10,12,10,6,0,-6,-10,-12,-10,-6,0};
char hy[]={-12,-10,-6,0,6,10,12,10,6,0,-6,-10,-12};

char xold=30,yold=30,xmold,ymold;
char hourd=0,mind=0,secd=0,count_clock=0;
bit hsecd=0,hmind=0,hhourd=0;


void hms_display(void)
{
 char x,y;
 char scr[20];
 

 sprintf(scr,"%d:%d:%d ",hourd,mind,secd); 
 glcd_moveto(80,  40);
 glcd_outtext(scr);
 
 glcd_setlinestyle(1,GLCD_LINE_SOLID);
 deleteclock(sec_radius, xold,yold);
 
 glcd_line(x_center_clock ,y_center_clock,(x_center_clock +sec_radius*cos6data[secd]/100),(y_center_clock-sec_radius*sin6data[secd]/100)); //sec 
 
 
 if (hmind==1)
 {
  deleteclock(min_radius,xmold,ymold);
  }
   
 glcd_line(x_center_clock ,y_center_clock,(x_center_clock +min_radius*cos6data[mind]/100),(y_center_clock-min_radius*sin6data[mind]/100)); //min
 x=hx[hourd]+(mind*(hx[hourd+1]-hx[hourd]))/60;
 y=hy[hourd]+(mind*(hy[hourd+1]-hy[hourd]))/60;
  
glcd_line(x_center_clock ,y_center_clock,(x_center_clock+x),(y_center_clock+y)); //min 
 yold=secd;
 xold=secd;
 xmold=mind;
 ymold=mind;
 }
 
 
// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Reinitialize Timer1 value
TCNT1H=0xD8F0 >> 8;
TCNT1L=0xD8F0 & 0xff;
// Place your code here
 count_clock++;
 //if (count==50)clockdisplay();
 if (count_clock==20)
 {
     count_clock=0; 
     secd++;
     hsecd==1;
     if (secd==60)
     {
        secd=0;
        mind++;
        hmind=1;
        if (mind==60){
        hourd++;
        hhourd=1;
        mind=0;
        if (hourd==12)hourd=0;
        }
        }
     
     hms_display();
 }
 
}



void timer1_init(void)
{
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0xD8;
TCNT1L=0xF0;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// Global enable interrupts
}



 


 
/****************************/
void clockdisplay(void)
{
 char scr[10];
char i,j,alfa,beta;

glcd_outtext("Hello");

glcd_outtextxy(0,40,"Time");
sprintf(scr,"%2d:%2d:%2d",10,30,9);
//glcd_outtextxy(30,20,"in the name of god");
glcd_outtextxy(0,50,scr);

glcd_setlinestyle(3,4);

glcd_circle(80,30,30); //clock circle
glcd_circle(80,30,2); //clock circle

glcd_setlinestyle(1,GLCD_LINE_SOLID);


 for (i=0;i<60;i++)
 {
  glcd_setlinestyle(1,GLCD_LINE_SOLID);
  
  glcd_setpixel( 80+25*cos6data[i]/100, (30+25*sin6data[i]/100)); 
  
  if((i==0)||(i==15)||(i==30)||(i==45))
  { 
 
  glcd_setpixel( 80+25*cos6data[i]/100, (30+25*sin6data[i]/100));
  glcd_setpixel( 80+24*cos6data[i]/100, (30+24*sin6data[i]/100));
  glcd_setpixel( 80+23*cos6data[i]/100, (30+23*sin6data[i]/100));
  glcd_setpixel( 80+22*cos6data[i]/100, (30+22*sin6data[i]/100));
  
  glcd_line((80+22*sin6data[i]/100),(30+20*cos6data[i]/100),(80+25*sin6data[i]/100),(30+25*cos6data[i]/100));
 }
 
 if((i==5)||(i==10))
  
 { 
 alfa=25*cos6data[i]/100;
 beta=25*sin6data[i]/100;
 glcd_setpixel( 80+alfa, 30+beta); 
 for (j=0;j<2;j++)glcd_setpixel( 80+alfa-j, 30+beta-j);
 }
 if((i==40)||(i==35))
  
 { 
 alfa=25*cos6data[i]/100;
 beta=25*sin6data[i]/100;
 glcd_setpixel( 80+alfa, 30+beta); 
 for (j=0;j<2;j++)glcd_setpixel( 80+alfa+j, 30+beta+j);
 }
 if((i==20)||(i==25))
  
 { 
 alfa=25*cos6data[i]/100;
 beta=25*sin6data[i]/100;
 glcd_setpixel( 80+alfa, 30+beta); 
 for (j=0;j<2;j++)glcd_setpixel( 80+alfa-j, 30+beta+j);
 }
 if((i==50)||(i==55))
  
 { 
 alfa=25*cos6data[i]/100;
 beta=25*sin6data[i]/100;
 glcd_setpixel( 80+alfa, 30+beta); 
 for (j=0;j<2;j++)glcd_setpixel( 80+alfa+j, 30+beta-j);
 }
 } 
 
  }

