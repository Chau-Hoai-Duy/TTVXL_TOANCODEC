#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
signed int8 T0,T0_TAM=0;
void main()
{
   system_init();
   s7seg.led[0]=0xff-1-2-4-8;
   s7seg.led[1]=m7d[1];
   s7seg.led[2]=m7d[10];
   s7seg.led[3]=m7d[12];
   s7seg.led[4]=0xff-1-32-16-8;
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(6);
   while(true)
   {
      T0=get_timer0();
      if(T0!=T0_TAM)
      {
         s7seg.led[7]=m7d[T0/10%10];
         s7seg.led[6]=m7d[T0%10];
         T0_TAM=T0;
         if(T0>=14) set_timer0(7);
      }
      s7seg_display();
   }
}
