#define board D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_ds1307.c>
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(4,0);
   lcd_data("DS1307 CLOCK");
   if(ds1307_battery_check()==ERROR)
   {
      ds1307.second=0x00;
      ds1307.minute=0x00;
      ds1307.hour=0x00;
      ds1307_set_time(ds1307);
   }
   while(true)
   {
      if(ds1307_read_time()==ok)
      {
         lcd_goto(6,1);
         printf(lcd_data,"%d%d:%d%d:%d%d",
                           ds1307.hour/16, ds1307.hour%16,
                           ds1307.minute/16, ds1307.minute%16,
                           ds1307.second/16, ds1307.second%16);
      }
   }
}
