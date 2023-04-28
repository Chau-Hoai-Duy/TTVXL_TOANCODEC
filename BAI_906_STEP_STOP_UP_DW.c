#define board D501
#include<tv_boards.c>
#include<tv_stepmotor.c>
unsigned int8 capdo=0;
unsigned int1 ttquay=0;
void main()
{
   system_init();
   stepmotor.time_per_step=capdo*5;
   stepmotor.direct=stepmotor_direct_forward;
   stepmotor.mode=stepmotor_mode_fullstep;
   d7seg.led[3]=m7d[0];
   d7seg.led[2]=m7d[0];
   d7seg.led[1]=m7d[0];
   d7seg.led[0]=m7d[0];
   d7seg_display();
   while(true)
   {
      if(inputcd(up)==0&&capdo<9)   
      {
         capdo++;
         stepmotor.time_per_step=(10-capdo)*5;
         ttquay=1;
      }
      if(inputcd(dw)==0&&capdo>0)
      {
         capdo--;
         stepmotor.time_per_step=(10-capdo)*5;
      }
      if(inputcd(mod)==0) 
      {
         ttquay=0;
         capdo=0;
         stepmotor.step=0;
      }
      if(capdo==0) ttquay=0;
      if(ttquay==1)
      {  
         stepmotor_control();
      }
      d7seg.led[3]=m7d[capdo];
      d7seg.led[2]=m7d[stepmotor.step/100%10];
      d7seg.led[1]=m7d[stepmotor.step/10%10];
      d7seg.led[0]=m7d[stepmotor.step%10];
      d7seg_display();
   }
}
