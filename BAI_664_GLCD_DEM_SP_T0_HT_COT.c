#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
unsigned int16 dem=0,i=0;
void main()
{
   system_init();
   glcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   while(true)
   {
      dem=get_timer0();
      if(dem>=1000) set_timer0(1);
      if(dem==0)
      {
         glcd_bar(1,35,1,0,3,0);
         glcd_bar(6,35,6,0,3,0);
         glcd_bar(11,35,11,0,3,0);
      }
      else
      {
         glcd_bar(1,35,1,35-(dem*3),3,1);
         for(i=1;i<9;i++)
         {
            glcd_line(1,(35-(i*3)),3,(35-(i*3)),0);
         }
      }
      glcd_update();
   }
}
