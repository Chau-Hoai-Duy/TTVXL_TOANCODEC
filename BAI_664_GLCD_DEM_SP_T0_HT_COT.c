#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
unsigned int16 dem=0,i=0, tram=0, chuc=0, dv=0;
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
      tram=dem/100;
      chuc=dem/10%10;
      dv=dem%10;
      glcd_rect(0,0,63,63,1,0);
      for(i=0;i<tram;i++)
      {
         glcd_rect(5,62-(i*5),10,62-(i*5+2),1,1);
      }
      for(i=0;i<chuc;i++)
      {
         glcd_rect(15,62-(i*5),20,62-(i*5+2),1,1);
      }
      for(i=0;i<dv;i++)
      {
         glcd_rect(25,62-(i*5),30,62-(i*5+2),1,1);
      }
      glcd_update();
   }
}
