#DEFINE BOARD D501
#include <tv_boards.c>
unsigned int8 phut=0,giay=0;
void main()
{
   system_init();
   while(true)
   {
      if(giay<59)
         giay++;
      else
      {
         giay=0;
         phut++;
         if (phut>=59) phut=0;
      }
      d7seg.led[0]=m7d[giay%10];
      d7seg.led[1]=m7d[giay/10%10];
      d7seg.led[2]=m7d[phut%10];
      d7seg.led[3]=m7d[phut/10%10];
      d7seg_display();
      delay_ms(500);
   }
}


