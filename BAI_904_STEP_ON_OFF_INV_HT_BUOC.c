#define board D501
#include<tv_boards.c>
#include<tv_stepmotor.c>
int1 ttquay=0;
void main()
{
   system_init();
   stepmotor.time_per_step=50;
   stepmotor.direct=stepmotor_direct_forward;
   stepmotor.mode=stepmotor_mode_halfstep;
   d7seg.led[3]=m7d[0];
   d7seg.led[2]=m7d[0];
   d7seg.led[1]=m7d[0];
   d7seg.led[0]=m7d[0];
   d7seg_display();
   while(true)
   {
      if(inputcd(on)==0)   ttquay=1;
      if(inputcd(off)==0)  ttquay=0;
      if(ttquay==1)
      {  
         if(inputcd(inv)==0) 
         {
            stepmotor.direct=~stepmotor.direct;
            stepmotor.step=0;
         }
         d7seg.led[3]=m7d[stepmotor.step/1000%10];
         d7seg.led[2]=m7d[stepmotor.step/100%10];
         d7seg.led[1]=m7d[stepmotor.step/10%10];
         d7seg.led[0]=m7d[stepmotor.step%10];
         d7seg_display();
         stepmotor_control();
      }
   }
}
