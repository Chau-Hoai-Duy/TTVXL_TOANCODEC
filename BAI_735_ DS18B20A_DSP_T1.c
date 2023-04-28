#define board D501
#include<tv_boards.c>
#include<tv_ds18b20.c>
unsigned int16 ng;
unsigned int8 sp;
void main()
{
   system_init();
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(98);
   ds18b20_set_resolution(9); delay_us(20);
   while(true)
   {
      /*************************************dem sp*********************************/
      sp=get_timer0();
      if(sp>=100) set_timer0(1);
      d7seg.led[3]=m7d[sp/10%10];
      d7seg.led[2]=m7d[sp%10];
      /*************************************do nhiet do****************************************/
      if(ds18b20_read_temperature()==ok)
      {
         ng=ds18b20.temperatureA>>4;
         d7seg.led[1]=m7d[ng/10%10];
         d7seg.led[0]=m7d[ng%10];
      }
      d7seg_display();
   }
}
