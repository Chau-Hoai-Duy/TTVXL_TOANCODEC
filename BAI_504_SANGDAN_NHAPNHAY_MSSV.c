//#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int8 mssv[8]={2, 0, 1, 4, 2, 1, 5, 7};
unsigned int1 tt=0;
signed int8 i,n,k;
void kt_nutnhan()
{
   if(inputcd(on)==0) tt=1;
   if(inputcd(off)==0)
   {
      tt=0;
      break;
   }
}
void main()
{
   system_init();
   tt=0;
   i=7;
   while(true)
   {
      kt_nutnhan();
      if(tt==1)
      {
            s7seg.led[0]=s7seg.led[1];
            s7seg.led[1]=s7seg.led[2];
            s7seg.led[2]=s7seg.led[3];
            s7seg.led[3]=s7seg.led[4];
            s7seg.led[4]=s7seg.led[5];
            s7seg.led[5]=s7seg.led[6];
            s7seg.led[6]=s7seg.led[7];
            if(i>=0)
            {
               s7seg.led[7]=m7d[mssv[i]];
               i--;
               for(n=0;n<100;n++) 
               {
                  s7seg_display();
                  kt_nutnhan();
               }
            }
         else if(i<0)
         {
               s7seg.led[7]=m7d[2];
               s7seg.led[6]=m7d[0];
               s7seg.led[5]=m7d[1];
               s7seg.led[4]=m7d[4];
               s7seg.led[3]=m7d[2];
               s7seg.led[2]=m7d[1];
               s7seg.led[1]=m7d[5];
               s7seg.led[0]=m7d[7];
               for(n=0;n<100;n++) 
               {
                  s7seg_display();
                  kt_nutnhan();
               }
               s7seg.led[7]=0xff;
               s7seg.led[6]=0xff;
               s7seg.led[5]=0xff;
               s7seg.led[4]=0xff;
               s7seg.led[3]=0xff;
               s7seg.led[2]=0xff;
               s7seg.led[1]=0xff;
               s7seg.led[0]=0xff;
               for(n=0;n<100;n++)
               {
                  s7seg_display();
                  kt_nutnhan();
               }
               i=-1;
         }
      }
      else if(tt==0)
      {
         for(k=0;k<8;k++)
         {
            s7seg.led[k]=0xff;
            s7seg_display();
         }
         i=7;
      }
   }
}
