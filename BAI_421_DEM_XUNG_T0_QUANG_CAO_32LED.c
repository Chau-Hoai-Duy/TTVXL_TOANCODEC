#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int8 T0=0,T0old=0,n=0,hu=0;
void d7seg_xoa0VN(unsigned int16 d)
{
   unsigned int8 m=0;
   do
   { d7seg.led[m]= m7d[d%10];
      d/=10;m++;
   }while(d!=0);
   for(;m<4;m++) d7seg.led[m]= 0xff;
   d7seg_display();
}
void sangdan_pst()
{
   if(n<=32)
   {
      led32.ledx32= ~(0xffffffff<<n);
      led32_display();
      delay_ms(50);
      n++;
   }
   else n=0;
}
void sangdan_tsp()
{
if(n<=32)
   {
      led32.ledx32= ~(0xffffffff>>n);
      led32_display();
      delay_ms(50);
      n++;
   }
   else n=0;
}
void tatdan_pst()
{
   if(n<=32)
   {
      led32.ledx32= 0xffffffff<<n;
      led32_display();
      delay_ms(50);
      n++;
   }
   else n=0;
}
void tatdan_tsp()
{
   if(n<=32)
   {
      led32.ledx32= 0xffffffff>>n;
      led32_display();
      delay_ms(50);
      n++;
   }
   else n=0;
}
void main()
{
   system_init();
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   while(true)
   {
      T0=get_timer0();
      if(T0>100) T0=1;
      if(T0!=T0old)
      {
         T0old=T0;
         d7seg_xoa0VN(T0);
      }
      if((inputcd(up)==0)&&hu<3) 
      {
         hu++;
         n=0;
      }
      if((inputcd(dw)==0)&&hu>0) 
      {
         hu--;
         n=0;
      }
      if(hu==0) sangdan_pst();
      else if(hu==1) sangdan_tsp();
      else if(hu==2) tatdan_pst();
      else tatdan_tsp();
   }
}
