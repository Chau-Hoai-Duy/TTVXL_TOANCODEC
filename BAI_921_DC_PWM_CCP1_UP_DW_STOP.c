#define board D501
#include<tv_boards.c>
#include<tv_dcmotor.c>
void main()
{
   system_init();
   dcmotor.direct=dcmotor_direct_forward;
   dcmotor.duty=0;
   while(true)
   {
      if(!inputcd(up)&&dcmotor.duty<1000) 
      {
         dcmotor.duty+=50;
      }
      if(!inputcd(dw)&&dcmotor.duty>0) 
      {
         dcmotor.duty-=50;
      }
      if(inputcd(inv)==0)
      {
         dcmotor.duty=0;
      }
      dcmotor_control();
      d7seg.led[1]=m7d[dcmotor.duty/50/10%10];
      d7seg.led[0]=m7d[dcmotor.duty/50%10];
      d7seg_display();
   }
}
