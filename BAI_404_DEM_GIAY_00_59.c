#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int8 giay;
void main()
{
   system_init();
   while(true)
      { 
         for(giay=0;giay<60;giay++)
         {
            d7seg.led[0]=m7d[giay%10];
            d7seg.led[1]=m7d[giay/10%10];
            d7seg_display();
            delay_ms(1000);
         }
      }    
}
