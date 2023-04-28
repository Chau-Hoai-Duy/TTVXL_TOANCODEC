#define board D501
#include<tv_boards.c>
#include<tv_stepmotor.c>
int1 ttquay=0;
void main()
{
   system_init();
   stepmotor.time_per_step=10;
   stepmotor.direct=stepmotor_direct_forward;
   stepmotor.mode=stepmotor_mode_halfstep;
   while(true)
   {
      if(inputcd(on)==0)   ttquay=1;
      if(inputcd(off)==0)  ttquay=0;
      if(ttquay==1)
      {  
         if(inputcd(inv)==0) stepmotor.direct=~stepmotor.direct;
         stepmotor_control();
      }
   }
}
