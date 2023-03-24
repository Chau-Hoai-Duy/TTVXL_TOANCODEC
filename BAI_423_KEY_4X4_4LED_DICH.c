#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_key4x4.c>
signed int8 i;
void main()
{
   system_init();
   d7seg.led[0]=0xff-128;
   d7seg.led[1]=0xff-128;
   d7seg.led[2]=0xff-128;
   d7seg.led[3]=0xff-128;
   d7seg_display();
   while(true)
   {
      if(key4x4_read()==ok)
      {
         delay_ms(50);
         
         
         for(i=3;i>0;i--)
         d7seg.led[i]=d7seg.led[i-1];
         d7seg.led[0]=m7d[key4x4.key];
         d7seg_display();
      }
   }
}
