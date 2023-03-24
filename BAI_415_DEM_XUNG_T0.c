#DEFINE BOARD D501
#include <tv_boards.c>
unsigned int16 T0;
void main()
{
   system_init();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(250);
   while(true)
   {
      T0=get_timer0();
      if(T0>=301) set_timer0(250);
      d7seg.led[2]=m7d[T0/100%10];
      d7seg.led[1]=m7d[T0/10%10];
      d7seg.led[0]=m7d[T0%10];
      d7seg_display();
   }
}


