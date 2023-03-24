#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int8 i;
signed int8 giay;
void main()
{
   system_init();
   while(true)
      { 
         if(i==0)
         {
            for(giay=0;giay<60;giay++)
            {
               d7seg.led[0]=m7d[giay%10];
               d7seg.led[1]=m7d[giay/10%10];
               d7seg_display();
               delay_ms(200);
            }
            delay_ms(3000);
            i++;
         }
         if(i==1)
         {  
            for(giay=59;giay>-1;giay--)
            {
               d7seg.led[0]=m7d[giay%10];
               d7seg.led[1]=m7d[giay/10%10];
               d7seg_display();
               delay_ms(200);
            }
            delay_ms(3000);
            i++;
         }
            if(i>=2) i=0;
      }    
}
