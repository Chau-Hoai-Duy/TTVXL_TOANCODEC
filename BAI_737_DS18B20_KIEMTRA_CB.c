#define board D501
#include<tv_boards.c>
#include<tv_ds18b20.c>
#include<tv_lcd.c>
unsigned int16 nga,tpa,ngb,tpb;
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("DS18B20A  DS18B20B");
   ds18b20_set_resolution(11);
   while(true)
   {
      if(ds18b20_read_temperature()==ok)
      {
         if(ds18b20.mumber_of_ds18b20==2)
         {
            nga=ds18b20.temperatureA>>4;
            tpa=(ds18b20.temperatureA&0x0f)*100/16;
            lcd_write_2x3_num(nga/10%10,0,1);
            lcd_write_2x3_num(nga/1%10,3,1);
            printf(lcd_data,".%ld",tpa);
            
            ngb=ds18b20.temperatureB>>4;
            tpb=(ds18b20.temperatureB&0x0f)*100/16;
            lcd_write_2x3_num(ngb/10%10,11,1);
            lcd_write_2x3_num(ngb/1%10,14,1);
            printf(lcd_data,".%ld",tpb);
         }
         else if(ds18b20.mumber_of_ds18b20==1)
         {
            lcd_write_2x3_num(10,11,1);
            lcd_write_2x3_num(10,14,1);
            lcd_goto(17,2);
            lcd_data("   ");
            nga=ds18b20.temperatureA>>4;
            tpa=(ds18b20.temperatureA&0x0f)*100/16;
            lcd_write_2x3_num(nga/10%10,0,1);
            lcd_write_2x3_num(nga/1%10,3,1);
            printf(lcd_data,".%ld",tpa);
            lcd_goto(12,1);
            lcd_data("CB HU");
         }
      }
   }
}
