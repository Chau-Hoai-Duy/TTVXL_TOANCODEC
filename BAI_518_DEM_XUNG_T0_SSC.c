#DEFINE BOARD D501
#include<tv_boards.c>
signed int8 dem=0;
void kt_nutnhan()
{
   if(inputcd(on)==0) setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   else if(inputcd(off)==0) setup_timer_0(T0_OFF);
   else if(inputcd(clr)==0)
   {
      dem=0;
      set_timer0(0);
   }
}
void main()
{
   system_init();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   while(true)
   {
      kt_nutnhan();
      dem=get_timer0();
      if(dem>=100) set_timer0(1);
      s7seg.led[0]=m7d[dem%10];
      s7seg.led[1]=m7d[dem/10%10];
      s7seg_display();
   }
}
