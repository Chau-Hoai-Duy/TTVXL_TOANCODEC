#define board D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_ds1307.c>
unsigned int1 mode=0;
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
      if(inputcd(mod)==0) 
      {
         mode=~mode;
         lcd_command(lcd_clear_display); delay_ms(2);
      }
      if(ds1307_read_time()==ok)
      {
         if(mode==1)
         {
            lcd_write_4x3_num(ds1307.hour/16,0);   
            lcd_write_4x3_num(ds1307.hour%16,3);
            lcd_write_4x3_num(ds1307.minute/16,7);
            lcd_write_4x3_num(ds1307.minute%16,10);
            lcd_write_4x3_num(ds1307.second/16,14);                    
            lcd_write_4x3_num(ds1307.second%16,17);
         }
         else if(mode==0)
         {
            lcd_goto(6,0);
            printf(lcd_data,"%d%d:%d%d:%d%d",
                              ds1307.hour/16, ds1307.hour%16,
                              ds1307.minute/16, ds1307.minute%16,
                              ds1307.second/16, ds1307.second%16);
         }
      }
   }
}
