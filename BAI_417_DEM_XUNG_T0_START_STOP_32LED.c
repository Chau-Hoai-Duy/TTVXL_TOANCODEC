#DEFINE BOARD D501
#include <tv_boards.c>
unsigned int8 T0=0, T0old=0;
unsigned int1 cd;
void d7seg_xoa0VN(unsigned int16 d)
{
   unsigned int8 n=0;
   do
   {  d7seg.led[n]= m7d[d%10];
      d/=10;n++;
   }while(d!=0);
   for(;n<4;n++) d7seg.led[n]= 0xff;
   d7seg_display();
}
void kt_nut_nhan()
{
   if(inputcd(on)==0)
   {
      setup_timer_0(t0_ext_h_to_l|t0_div_1);
      cd=1;
   }
   if(inputcd(off)==0)
   {
      setup_timer_0(t0_off);
      cd=0;
   }
}
void main()
{
   system_init();
   setup_timer_0(t0_off);
   set_timer0(0);
   cd=0;
   while(true)
   {
      T0=get_timer0();
      if(T0>100) set_timer0(1);
      kt_nut_nhan();
      if(cd==0) led32.ledx32=0;
      else if(cd==1) led32.ledx32=0xffffffff;
      led32_display();
      if(T0!=T0old)
      {
         T0old=T0;
         d7seg_xoa0VN(T0);
      }
   }
}
