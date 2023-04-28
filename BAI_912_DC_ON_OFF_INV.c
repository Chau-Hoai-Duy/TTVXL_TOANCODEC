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
      if(!inputcd(on)) 
      {
         dcmotor.duty=1000;
      }
      if(!inputcd(off)) 
      {
         dcmotor.duty=0;
      }
      if((inputcd(inv)==0)&&(dcmotor.duty!=0))
      {
         dcmotor.direct=~dcmotor.direct;
      }
      dcmotor_control();
      led32_display();
   }
}
