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
         led32.ledx8[0]=0xff;
      }
      if(!inputcd(off)) 
      {
         dcmotor.duty=0;
         led32.ledx8[0]=0x00;
      }
      dcmotor_control();
      led32_display();
   }
}
