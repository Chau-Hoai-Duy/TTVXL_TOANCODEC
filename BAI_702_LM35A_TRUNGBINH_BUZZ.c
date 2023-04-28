#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int16 lm351=0,i, tong=0;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_TO_AN2|VSS_VDD);
   set_adc_channel(0); delay_us(20);
   while(true)
   {
      tong=0;
      for(i=0;i<100;i++)
      {
         tong=tong+read_adc()/2.046;
         delay_ms(1);
      }
         lm351=tong/100;
         d7seg.led[0]=m7d[lm351%10];
         d7seg.led[1]=m7d[lm351/10%10];
         d7seg_display();
         if(lm351>40) led32.ledx1[0]=1;
         else if(lm351<=40) led32.ledx1[0]=0;
         led32_display();
   }
}
