#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
#include<math.h>
unsigned int8 bdn=0;
signed int8 giay=0;
unsigned int8 x,y;

void main()
{
   system_init();
   glcd_setup();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   glcd_circle(64,31,31,0,1);
   glcd_text_setup(89,3,1,1,1);
   glcd_text("12");
   glcd_text_setup(119,28,1,1,1);
   glcd_text("3");
   glcd_text_setup(93,54,1,1,1);
   glcd_text("6");
   glcd_text_setup(66,28,1,1,1);
   glcd_text("9");
   glcd_update();
   while(true)
   {
      if(bdn>=10)
      {
         bdn-=10;
         giay++;
         if(giay>=60) giay=0;
         glcd_circle(95,31,21,1,0);
         glcd_bar(95,31,95+18*cos((giay-15)*pi/30),31+18*sin((giay-15)*pi/30),2,1);
         glcd_update();
      }
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}



//#define   BOARD     D501  
//!#include<tv_boards.c>
//!#include<tv_glcd.c>  
//!#include<math.h>
//!unsigned int8 bdn=0;
//!signed char giay=0;
//!void main()
//!{
//!      system_init();  
//!      glcd_setup();
//!      setup_timer_1(t1_internal|t1_div_by_8);
//!      set_timer1(3036);
//!      enable_interrupts(int_timer1);
//!      enable_interrupts(global);
//!      glcd_circle(95,31,31,1,1);
//!      glcd_circle(95,31,28,1,0);
//!      glcd_text_setup(90,4,1,1,0); glcd_text("12");
//!      glcd_text_setup(93,52,1,1,0); glcd_text("6");
//!      glcd_text_setup(116,26,1,1,0); glcd_text("3");
//!      glcd_text_setup(70,26,1,1,0); glcd_text("9");
//!      while(true)
//!      {    
//!            if (bdn>=10)
//!            {
//!              bdn=bdn-10;
//!              giay++;
//!              giay%=60;                     
//!            }
//!            glcd_circle(95,31,18,1,0);
//!            glcd_bar(95,31,95+16*cos((giay-15)*pi/30),31+16*sin((giay-15)*pi/30),2,1);
//!            glcd_update();                    
//!      }
//!}
//!#int_timer1
//!void ngat_timer1()
//!{
//!     set_timer1(3036);
//!     bdn++;
//!}
