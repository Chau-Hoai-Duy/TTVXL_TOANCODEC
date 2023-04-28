#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#define solan 100
unsigned int16 lm351=0,dem=0,i=0, tong=0;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_TO_AN2|VSS_VDD);
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   set_adc_channel(0); delay_us(20);
   while(true)
   {
      dem=get_timer0();
      if(dem>=100) set_timer0(1);
      tong+=read_adc()/2.046;
      if(i>=solan)
      {
         lm351=tong/100;
         tong=0;
         i=0;
      }
      else i++;
      /***************************************Xu ly hien thi***************************************/
      d7seg.led[0]=m7d[lm351%10];
      d7seg.led[1]=m7d[lm351/10%10];
      d7seg.led[2]=m7d[dem%10]-128;
      d7seg.led[3]=m7d[dem/10%10];
      d7seg_display();
   }
}
