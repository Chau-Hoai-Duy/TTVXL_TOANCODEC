#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
#include<tv_lcd.c>
unsigned int8 dem=0;
unsigned int1 tt=0;
void kt_nutnhan()
{
   if(inputcd(inv)==0)
   {
      tt=~tt;
      glcd_circle(95,32,17,0,0);
      glcd_line(75,32,95,12,0);
      glcd_line(95,12,115,32,0);
      glcd_line(115,32,95,52,0);
      glcd_line(95,52,75,32,0);
      glcd_update();
   }
}
void main()
{
   system_init();
   glcd_setup();
   glcd_spkt_logo_raw(0);
   glcd_update();
   lcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   while(true)
   {
      kt_nutnhan();
      dem=get_timer0();
      if(dem>=99) set_timer0(1);
      /***************************************HIEN THI TREN LED 7 DOAN********************************/
      d7seg.led[0]=m7d[dem%10];
      d7seg.led[1]=m7d[dem/10%10];
      d7seg_display();
      /****************************HIEN THI LCD***********************************************/
      lcd_goto(0,0);
      lcd_data(dem/10%10+48);
      lcd_data(dem%10+48);
      lcd_write_2x3_num(dem/10%10,4,1);
      lcd_write_2x3_num(dem%10,7,1);
      lcd_write_4x3_num(dem/10%10,14);
      lcd_write_4x3_num(dem%10,17);\
      /******************************HIEN THI GLCD*********************************************/
      glcd_text_setup(85,25,2,1,1);
      printf(glcd_text,"%02d",dem);
      glcd_update();
      if(tt==0)
      {
         glcd_circle(95,32,17,0,1);
         glcd_update();
      }
      if(tt==1)
      {
         glcd_line(75,32,95,12,1);
         glcd_line(95,12,115,32,1);
         glcd_line(115,32,95,52,1);
         glcd_line(95,52,75,32,1);
         glcd_update();
      }
   }
}
