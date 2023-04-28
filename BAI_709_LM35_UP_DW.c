#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#define solan 100
unsigned int16 lm351=0,i=0, tong=0, gtcai=35;
void kt_nutnhan()
{
   if(inputcd(up)==0)
   {
      gtcai++;
      if(gtcai>=60) gtcai=60;
   }
   if(inputcd(dw)==0)
   {
      gtcai--;
      if(gtcai<=35) gtcai=35;
   }
}
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_TO_AN2|VSS_VDD);
   set_adc_channel(0); delay_us(20);
   while(true)
   {
      kt_nutnhan();
      tong+=read_adc()/2.046;
      if(i>=solan)
      {
         lm351=tong/100;
         tong=0;
         i=0;
      }
      else i++;
      if(lm351>gtcai)
      {
         triac_2_off();
         led32.ledx1[0]=1;
      }
      else if(lm351<(gtcai-5))
      {
         triac_2_on();
      }
      else led32.ledx1[0]=0;
      /***************************************Xu ly hien thi***************************************/
      d7seg.led[0]=m7d[lm351%10];
      d7seg.led[1]=m7d[lm351/10%10];
      d7seg.led[2]=m7d[gtcai%10]-128;
      d7seg.led[3]=m7d[gtcai/10%10];
      led32_display();
      d7seg_display();
   }
}
