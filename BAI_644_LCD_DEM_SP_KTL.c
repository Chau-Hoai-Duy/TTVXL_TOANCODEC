#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
unsigned int8 dem;
void main()
{
   system_init();
   lcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   lcd_goto(0,0);
   lcd_data("**DEM SAN PHAM**");
   while(true)
   {
      dem=get_timer0();
      if(dem>=101) set_timer0(1);
      lcd_write_2x3_num(dem/100%10,11,1);
      lcd_write_2x3_num(dem/10%10,14,1);
      lcd_write_2x3_num(dem%10,17,1);
      d7seg.led[0]=m7d[dem%10];
      d7seg.led[1]=m7d[dem/10%10];
      d7seg.led[2]=m7d[dem/100%10];
      d7seg_display();
      s7seg.led[0]=m7d[dem%10];
      s7seg.led[1]=m7d[dem/10%10];
      s7seg.led[2]=m7d[dem/100%10];
      s7seg_display();
   }
}
