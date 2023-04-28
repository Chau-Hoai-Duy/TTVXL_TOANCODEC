#define board D501
#include<tv_boards.c>
#include<tv_dcmotor.c>
unsigned int8 cap=0;
void main()
{
   system_init();
   dcmotor.direct=dcmotor_direct_forward;
   dcmotor.duty=0;
   while(true)
   {
      if(!inputcd(BT0)) 
      {
         dcmotor.duty=0;
         cap=0;
      }
      if(!inputcd(BT1)) 
      {
         dcmotor.duty=350;
         cap=1;
      }
      if(!inputcd(BT2)) 
      {
         dcmotor.duty=700;
         cap=2;
      }
      if(!inputcd(BT3)) 
      {
         dcmotor.duty=1000;
         cap=3;
      }
      dcmotor_control();
      d7seg.led[0]=m7d[cap];
      d7seg_display();
   }
}
