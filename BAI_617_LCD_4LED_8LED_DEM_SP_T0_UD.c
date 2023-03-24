//#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
unsigned int8 dem,gt_cai=1;
void kt_nutnhan()
{
   if(inputcd(clr)==0)
   {
      gt_cai=1;
      set_timer0(0);
   }
   if(inputcd(up)==0)
   {
      gt_cai++;
      if(gt_cai>=100) gt_cai=1;
      if(dem>gt_cai) set_timer0(1);
   }
   if(inputcd(dw)==0)
   {
      gt_cai--;
      if(gt_cai<=0) gt_cai=99;
      if(dem>gt_cai) set_timer0(1);
   }
}
void main()
{
   system_init();
   lcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   while(true)
   {
      dem=get_timer0();
      if(dem>gt_cai) set_timer0(1);
      kt_nutnhan();
      lcd_goto(9,0);
      lcd_data(gt_cai/10%10+48);
      lcd_data(gt_cai%10+48);
      lcd_goto(9,1);
      lcd_data(dem/10%10+48);
      lcd_data(dem%10+48);
      d7seg.led[0]=m7d[dem%10];
      d7seg.led[1]=m7d[dem/10%10];
      d7seg.led[2]=m7d[gt_cai%10];
      d7seg.led[3]=m7d[gt_cai/10%10];
      d7seg_display();
      s7seg.led[0]=m7d[dem%10];
      s7seg.led[1]=m7d[dem/10%10];
      s7seg.led[6]=m7d[gt_cai%10];
      s7seg.led[7]=m7d[gt_cai/10%10];
      s7seg_display();
   }
}
