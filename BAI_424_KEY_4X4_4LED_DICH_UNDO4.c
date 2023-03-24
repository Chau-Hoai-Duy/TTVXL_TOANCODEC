//#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_key4x4.c>
signed int8 i,dem,dl1,dl2,dl3,dl4;
void main()
{
   system_init();
   d7seg.led[0]=0xff-128;
   d7seg.led[1]=0xff-128;
   d7seg.led[2]=0xff-128;
   d7seg.led[3]=0xff-128;
   dem=0;
   i=3;
   d7seg_display();
   while(true)
   {
      if(key4x4_read()==ok)
      {
         if((key4x4.key<=9))
         {
            delay_ms(50);
            dl4=dl3;
            dl3=dl2;
            dl2=dl1;
            dl1=d7seg.led[3];
            d7seg.led[3]=d7seg.led[2];
            d7seg.led[2]=d7seg.led[1];
            d7seg.led[1]=d7seg.led[0];
            d7seg.led[0]=m7d[key4x4.key];
            d7seg_display();
            dem=0;
         }
         else if(key4x4.key==12)
         {
            d7seg.led[0]=0xff-128;
            d7seg.led[1]=0xff-128;
            d7seg.led[2]=0xff-128;
            d7seg.led[3]=0xff-128;
            dem=0;
            d7seg_display();
         }
         else if((key4x4.key==11)&&(dem!=4))
         {
            dem++;
            d7seg.led[0]=d7seg.led[1];
            d7seg.led[1]=d7seg.led[2];
            d7seg.led[2]=d7seg.led[3];
            d7seg.led[3]=dl1;
            dl1=dl2;
            dl2=dl3;
            dl3=dl4;
            d7seg_display();
         }
      }
   }
}
