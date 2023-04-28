#define board D501
#include<tv_boards.c>
#include<tv_stepmotor.c>
#include<tv_key4x4.c>
signed int32 sovongcai=0, sovong=0,sovongcu=0;
unsigned int1 ttquay=0;
void main()
{
   system_init();
   stepmotor.time_per_step=10;
   stepmotor.direct=stepmotor_direct_forward;
   stepmotor.mode=stepmotor_mode_fullstep;
   d7seg.led[0]=m7d[sovongcai];
   while(true)
   {
      if(key4x4_read()==ok)
      {
         if((key4x4.key<=9)&&(ttquay==0))
         {
            sovongcai=key4x4.key;
            d7seg.led[0]=m7d[sovongcai];
         }
         if(key4x4.key==0x0d)
         {
            ttquay=1;
         }
      }
      if(ttquay==1)
      {
         stepmotor_control();
      }
      if(stepmotor.step>=200)
      {
         stepmotor.step-=200;
         sovongcai--;
         if(sovongcai==0) ttquay=0;
      }
      d7seg.led[0]=m7d[sovongcai];
      d7seg_display();
   }
}
