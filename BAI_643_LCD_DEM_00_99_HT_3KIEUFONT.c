#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
unsigned int8 dem=0;
void main()
{
   system_init();
   lcd_setup();
   while(true)
   {
     for(dem=0;dem<100;dem++)
     {
         lcd_goto(0,2);
         lcd_data(dem/10%10+48);
         lcd_data(dem%10+48);
         lcd_write_2x3_num(dem/10%10,6,1);
         lcd_write_2x3_num(dem%10,9,1);
         lcd_write_4x3_num(dem/10%10,14);
         lcd_write_4x3_num(dem%10,17);
         delay_ms(500);
     }
   }
}
