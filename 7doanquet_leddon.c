#include<tv_boards.c>
unsigned int8 i=0;
unsigned int16 k=0;
void main()
{
   while(true)
   {
      system_init();
      for(i=0;i<32;i++)
      {
         led32.ledx32=~(0xffffffff<<i);
         led32_display();
         s7seg.led[0]=m7d[0];
         s7seg.led[1]=m7d[1];
         for(k=0;k<50;k++) s7seg_display();
      }
      
   }
}
