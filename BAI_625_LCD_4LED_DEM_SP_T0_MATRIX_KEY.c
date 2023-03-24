#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_key4x4.c>
#include<tv_lcd.c>
unsigned int8 dem,gt_cai=1,nnhan=0,stt;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key==12)
      {
         gt_cai=1;
         set_timer0(0);
         d7seg.led[3]=m7d[gt_cai/10%10];
         d7seg.led[2]=m7d[gt_cai%10];
         d7seg_display();
         s7seg.led[7]=m7d[gt_cai/10%10];
         s7seg.led[6]=m7d[gt_cai%10];
         lcd_goto(9,0);
         lcd_data(gt_cai/10%10+48);
         lcd_data(gt_cai%10+48);
      }
      if(key4x4.key<10)
      {
         if(nnhan==0)
         {
            gt_cai=key4x4.key*10;
            d7seg.led[3]=0xff;
            d7seg.led[2]=m7d[key4x4.key];
            stt=key4x4.key;
            d7seg_display();
            lcd_goto(9,0);
            lcd_data(' ');
            lcd_data(key4x4.key+48);
         }
         else if(nnhan==1)
         {
            gt_cai=gt_cai+key4x4.key;
            d7seg.led[3]=m7d[gt_cai/10%10];
            d7seg.led[2]=m7d[gt_cai%10];
            d7seg_display();
            s7seg.led[7]=m7d[gt_cai/10%10];
            s7seg.led[6]=m7d[gt_cai%10];
            lcd_goto(9,0);
            lcd_data(gt_cai/10%10+48);
            lcd_data(gt_cai%10+48);
         }
         nnhan++;
         if(nnhan>=2) nnhan=0;
      }
   }
   if(nnhan==1)
   {
      s7seg.led[7]=0xff;
      s7seg.led[6]=m7d[stt];
      s7seg_display();
   }
   else 
   {
      s7seg_display();
      d7seg_display();
   }
}
void main()
{
   system_init();
   lcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   lcd_goto(9,0);
   lcd_data(gt_cai/10%10+48);
   lcd_data(gt_cai%10+48);
   d7seg.led[2]=m7d[gt_cai%10];
   d7seg.led[3]=m7d[gt_cai/10%10];
   d7seg_display();
   s7seg.led[6]=m7d[gt_cai%10];
   s7seg.led[7]=m7d[gt_cai/10%10];
   while(true)
   {
      dem=get_timer0();
      if(dem>gt_cai) set_timer0(1);
      kt_nutnhan();
      lcd_goto(9,1);
      lcd_data(dem/10%10+48);
      lcd_data(dem%10+48);
      d7seg.led[0]=m7d[dem%10];
      d7seg.led[1]=m7d[dem/10%10];
      d7seg_display();
      s7seg.led[0]=m7d[dem%10];
      s7seg.led[1]=m7d[dem/10%10];
   }
}
