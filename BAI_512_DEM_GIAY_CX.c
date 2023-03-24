#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int8 giay,bdn;
void main()
{
   system_init();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while(true)
   {
      if(bdn>=10)
      {
         bdn=bdn-10;
         giay++;
         if(giay>=60) giay=0;
      }
      s7seg.led[0]=m7d[giay%10];
      s7seg.led[1]=m7d[giay/10%10];
      s7seg_display();
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
