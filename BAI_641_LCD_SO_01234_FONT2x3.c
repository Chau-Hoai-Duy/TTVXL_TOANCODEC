#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
void main()
{
   system_init();
   lcd_setup();
   lcd_write_2x3_num(0,0,1);
   lcd_write_2x3_num(1,4,1);
   lcd_write_2x3_num(2,8,1);
   lcd_write_2x3_num(3,12,1);
   lcd_write_2x3_num(4,16,1);
   while(true)
   {
     
   }
}
