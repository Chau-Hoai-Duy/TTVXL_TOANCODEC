#define board D501
#include<tv_boards.c>
#include<tv_ds18b20.c>
unsigned int16 ng,tp;
void main()
{
   system_init();
   ds18b20_set_resolution(9);
   while(true)
   {
      if(ds18b20_read_temperature()==ok)
      {
         ng=ds18b20.temperatureA>>4;
         tp=(ds18b20.temperatureA&0x0f)*10/16;
         d7seg.led[2]= m7d[ng/10%10];
         d7seg.led[1]= m7d[ng%10]-128;
         d7seg.led[0]= m7d[tp];
         d7seg_display();
      }
   }
}
