#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
#include<tv_lcd.c>
unsigned int8 dem=0;
void main()
{
   system_init();
   glcd_setup();
   glcd_spkt_logo_raw(0);
   glcd_update();
   glcd_circle(100,32,22,0,1);
   lcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   while(true)
   {
      dem=get_timer0();
      if(dem>=99) set_timer0(1);
      d7seg.led[0]=m7d[dem%10];
      d7seg.led[1]=m7d[dem/10%10];
      d7seg_display();
      lcd_goto(0,0);
      lcd_data(dem/10%10+48);
      lcd_data(dem%10+48);
      lcd_write_2x3_num(dem/10%10,4,1);
      lcd_write_2x3_num(dem%10,7,1);
      lcd_write_4x3_num(dem/10%10,14);
      lcd_write_4x3_num(dem%10,17);
      glcd_text_setup(83,22,3,1,1);
      printf(glcd_text,"%02d",dem);
      glcd_update();
   }
}
