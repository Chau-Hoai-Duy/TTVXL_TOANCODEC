#define board D501
#include<tv_boards.c>
#include<tv_ds18b20.c>
#include<tv_lcd.c>
unsigned int16 ng,tp;
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("DS18B20A  DS18B20B");delay_ms(2);
   ds18b20_set_resolution(11); delay_us(20);
   while(true)
   {
      if(ds18b20_read_temperature()==ok)
      {
         ng=ds18b20.temperatureA>>4;
         tp=(ds18b20.temperatureA&0x0f)*100/16;
         lcd_write_2x3_num(ng/10%10,0,1);
         lcd_write_2x3_num(ng/1%10,3,1);
         printf(lcd_data,".%ld",tp);
         
         ng=ds18b20.temperatureB>>4;
         tp=(ds18b20.temperatureB&0x0f)*100/16;
         lcd_write_2x3_num(ng/10%10,11,1);
         lcd_write_2x3_num(ng/1%10,14,1);
         printf(lcd_data,".%ld",tp);
      }
   }
}
