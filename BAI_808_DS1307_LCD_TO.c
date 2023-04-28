#define board D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_ds1307.c>
void main()
{
   system_init();
   lcd_setup();
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
         lcd_write_4x3_num(ds1307.hour/16,0);   
         lcd_write_4x3_num(ds1307.hour%16,3);
         lcd_write_4x3_num(ds1307.minute/16,7);
         lcd_write_4x3_num(ds1307.minute%16,10);
         lcd_write_4x3_num(ds1307.second/16,14);                    
         lcd_write_4x3_num(ds1307.second%16,17);            
      }
   }
}
