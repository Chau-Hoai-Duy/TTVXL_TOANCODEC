#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
#include<tv_key4x4.c>
#define solan 100
signed int8 bdn=0, cd=0, i=0, caitg=0, gt_spcai=0, gio=0, phut=0, giay=0, giaycu=0, dem=0, demcu=0,n=0;
unsigned int16 lm35a=0, lm35b=0, lm35acu=0, lm35bcu=0, tonga=0, tongb=0;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key==15)
      {
         cd++;
         i=0;
         if(cd>4) cd=0;
      }
      if(key4x4.key<10)
      {
         if(i==0)
         {
            caitg=key4x4.key*10;
            if(cd==4) gt_spcai=key4x4.key*10;
         }
         if(i==1)
         {
            caitg=caitg+key4x4.key;
            if(cd==4) gt_spcai=gt_spcai+key4x4.key;
         }
         i++;
         if(i>=2) i=0;
         if(cd==1)
         {
            gio=caitg;
            if(gio>=13) 
            {
               gio=1;
               i=0;
            }
         }
         if(cd==2)
         {
            phut=caitg;
            if(phut>=60)
            {
               phut=0;
               i=0;
            }
         }
         if(cd==3)
         {
            giay=caitg;
            if(giay>=60)
            {
               giay=0;
               i=0;
            }
         }
      }
   }
}
void do_ndo()
{
   set_adc_channel(0); delay_us(20);
   tonga+=read_adc()/2.046;
   if(n>=solan)
   {
      lm35a=tonga/100;
      tonga=0;
      n=0;
   }
   else n++;
   set_adc_channel(1); delay_us(20);
   tongb+=read_adc()/2.046;
   if(n>=solan)
   {
      lm35b=tongb/100;
      tongb=0;
      n=0;
   }
   else n++;
}
void nhapnhay_lcd()
{
   if(cd==1)
   {
      lcd_goto(0,0);
      lcd_data("      ");
      lcd_goto(0,1);
      lcd_data("      ");
   }
   if(cd==2)
   {
      lcd_goto(7,0);
      lcd_data("      ");
      lcd_goto(7,1);
      lcd_data("      ");
   }
   if(cd==3)
   {
      lcd_goto(14,0);
      lcd_data("      ");
      lcd_goto(14,1);
      lcd_data("      ");
   }
   if(cd==4)
   {
      lcd_goto(0,2);
      lcd_data("      ");
      lcd_goto(0,3);
      lcd_data("      ");
   }
}
void nhapnhay_glcd()
{
   if(lm35a>50)
   {
      glcd_text_setup(15,35,2,1,1);
      glcd_text("  ");
   }
   if(lm35b>50)
   {
      glcd_text_setup(145,35,2,1,1);
      glcd_text("  ");
   }
}
void ht_lcd()
{
   lcd_write_2x3_num(gio/10%10,0,0);
   lcd_write_2x3_num(gio%10,3,0);
   lcd_write_2x3_num(phut/10%10,7,0);
   lcd_write_2x3_num(phut%10,10,0);
   lcd_write_2x3_num(giay/10%10,14,0);
   lcd_write_2x3_num(giay%10,17,0);
   lcd_write_2x3_num(gt_spcai/10%10,0,2);
   lcd_write_2x3_num(gt_spcai%10,3,2);
   lcd_write_2x3_num(dem/10%10,14,2);
   lcd_write_2x3_num(dem%10,17,2);
}
void ht_tron_vuong()
{
   if(lm35a>lm35b)
   {
      glcd_circle(27,42,21,0,0);
      glcd_rect(13,28,41,56,0,1);
      glcd_circle(157,42,21,0,1);
      glcd_rect(143,28,171,56,0,0);
   }
   if(lm35b>lm35a)
   {
      glcd_circle(27,42,21,0,1);
      glcd_rect(13,28,41,56,0,0);
      glcd_circle(157,42,21,0,0);
      glcd_rect(143,28,171,56,0,1);
   }
   if(lm35b==lm35a)
   {
      glcd_circle(27,42,21,0,1);
      glcd_rect(13,28,41,56,0,0);
      glcd_circle(157,42,21,0,1);
      glcd_rect(143,28,171,56,0,0);
   }
}
void ht_glcd()
{
   if(lm35a!=lm35acu||lm35b!=lm35bcu||lm35a>50||lm35b>50)
   {
      nhapnhay_glcd();
      glcd_update();
      glcd_text_setup(15,35,2,1,1);
      printf(glcd_text,"%02lu",lm35a);
      glcd_text_setup(145,35,2,1,1);
      printf(glcd_text,"%02lu",lm35b);
      ht_tron_vuong();
      lm35acu=lm35a; lm35bcu=lm35b;
      glcd_update();
   }
}
void main()
{
   system_init();
   lcd_setup();
   glcd_setup();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_TO_AN2| VSS_VDD);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   glcd_circle(27,42,21,0,1);
   glcd_circle(157,42,21,0,1);
   glcd_text_setup(5,5,2,1,1);
   glcd_text("LM35A");
   glcd_text_setup(130,5,2,1,1);
   glcd_text("LM35B");
   glcd_update();
   while(true)
   {
      kt_nutnhan();
      do_ndo();
      /***********************************xu li thoi gian********************************/
      if(bdn>=10)
      {
         bdn=bdn-10;
         giay++;
         if(giay>=60)
         {
            giay=0;
            phut++;
            if(phut>=60)
            {
              phut=0;
              gio++;
              if(gio>=13) gio=1;
            }
         }
      }
      /*********************************xu li dem san pham**************************/
      dem=get_timer0();
      if(dem>gt_spcai) set_timer0(1);
      /*********************************xu li hien thi*****************************/
      ht_glcd();
      if((giay!=giaycu)||(dem!=demcu))
      {
         ht_lcd();
         giaycu=giay;demcu=dem;
      }
      
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
   if(cd!=0) nhapnhay_lcd();
}
