#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int16 lm351=0;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_TO_AN2|VSS_VDD);
   set_adc_channel(0); delay_us(20);
   while(true)
   {
      lm351=read_adc()/2.046;
      d7seg.led[0]=m7d[lm351%10];
      d7seg.led[1]=m7d[lm351/10%10];
      d7seg_display();
   }
}
