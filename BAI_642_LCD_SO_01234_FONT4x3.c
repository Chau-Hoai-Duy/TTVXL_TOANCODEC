#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
void main()
{
   system_init();
   lcd_setup();
   lcd_write_4x3_num(0,0);
   lcd_write_4x3_num(1,4);
   lcd_write_4x3_num(2,8);
   lcd_write_4x3_num(3,12);
   lcd_write_4x3_num(4,16);
   while(true)
   {
     
   }
}
