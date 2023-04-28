#define board D501
#include<tv_boards.c>
#include<tv_ds18b20.c>
unsigned int16 ng, lm35a=0, tonga=0;
unsigned int8 n=0;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins| Vss_Vdd);
   set_adc_channel(lm35a_channel); delay_us(20);
   ds18b20_set_resolution(9); delay_us(20);
   while(true)
   {
      /*************************************do lmm35a*********************************/
      tonga+=read_adc();
      if(n>=100)
      {
         lm35a=tonga/2.046/100;
         n=0;
         tonga=0;
      }
      else n++;
      d7seg.led[1]=m7d[lm35a/10%10];
      d7seg.led[0]=m7d[lm35a%10];
      /*************************************do nhiet do****************************************/
      if(ds18b20_read_temperature()==ok)
      {
         ng=ds18b20.temperatureA>>4;
         d7seg.led[3]=m7d[ng/10%10];
         d7seg.led[2]=m7d[ng%10];
      }
      d7seg_display();
   }
}
