#include<tv_boards.c>
#include<tv_glcd.c>
#include<tv_lcd.c>
#include<tv_key4x4.c>
signed int8 bdn=0, cd=0, i=0, caitg=0, gt_spcai=0, gio=0, phut=0, giay=0, dem=0;
unsigned int16 k;
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
void ht_glcd()
{
   if(cd==1)
      {
         glcd_circle(56,16,15,0,1);     //Hinh tron ban kinh 15, 
         glcd_text_setup(45,9,2,1,1);
         printf(glcd_text,"%02u",gio);
         glcd_text_setup(83,9,2,1,1);
         printf(glcd_text,"%02u",phut);
         glcd_text_setup(121,9,2,1,1);
         printf(glcd_text,"%02u",giay);
         glcd_text_setup(145,40,2,1,1);
         printf(glcd_text,"%02u ",dem);
         glcd_update();
      }
      else if(cd==2)
      {
         glcd_circle(56,16,15,0,0);
         glcd_circle(94,16,15,0,1);     //Hinh tron ban kinh 15, 
         glcd_text_setup(83,9,2,1,1);
         printf(glcd_text,"%02u",phut);
         glcd_text_setup(45,9,2,1,1);
         printf(glcd_text,"%02u",gio);
         glcd_text_setup(121,9,2,1,1);
         printf(glcd_text,"%02u",giay);
         glcd_text_setup(145,40,2,1,1);
         printf(glcd_text,"%02u ",dem);
         glcd_update();
      }
      else if(cd==3)
      {
         glcd_circle(94,16,15,0,0);
         glcd_circle(132,16,15,0,1);     //Hinh tron ban kinh 15, 
         glcd_text_setup(121,9,2,1,1);
         printf(glcd_text,"%02u",giay);
         glcd_text_setup(45,9,2,1,1);
         printf(glcd_text,"%02u",gio);
         glcd_text_setup(83,9,2,1,1);
         printf(glcd_text,"%02u",phut);
         glcd_text_setup(145,40,2,1,1);
         printf(glcd_text,"%02u ",dem);
         glcd_update();
      }
      else if(cd==4)
      {
         glcd_circle(132,16,15,0,0);
         glcd_circle(16,47,15,0,1);     //Hinh tron ban kinh 15, 
         glcd_text_setup(5,40,2,1,1);
         printf(glcd_text,"%02u",gt_spcai);
         glcd_text_setup(45,9,2,1,1);
         printf(glcd_text,"%02u",gio);
         glcd_text_setup(83,9,2,1,1);
         printf(glcd_text,"%02u",phut);
         glcd_text_setup(121,9,2,1,1);
         printf(glcd_text,"%02u",giay);
         glcd_text_setup(5,40,2,1,1);
         glcd_text_setup(145,40,2,1,1);
         printf(glcd_text,"%02u ",dem);
         glcd_update();
      }
      else
      {
         glcd_circle(16,47,15,0,0);
         glcd_text_setup(45,9,2,1,1);
         printf(glcd_text,"%02u",gio);
         glcd_text_setup(83,9,2,1,1);
         printf(glcd_text,"%02u",phut);
         glcd_text_setup(121,9,2,1,1);
         printf(glcd_text,"%02u",giay);
         glcd_text_setup(5,40,2,1,1);
         printf(glcd_text,"%02u",gt_spcai);
         glcd_text_setup(145,40,2,1,1);
         printf(glcd_text,"%02u ",dem);
         glcd_update();
      }
}
void nhapnhay()
{
   if(cd==1)
   {
      lcd_goto(0,0);
      lcd_data("      ");
      lcd_goto(0,1);
      lcd_data("      ");
      for(k=0;k<5;k++) 
      {
         kt_nutnhan();
         ht_glcd();
      }
      ht_lcd();
   }
   else if(cd==2)
   {
      lcd_goto(7,0);
      lcd_data("      ");
      lcd_goto(7,1);
      lcd_data("      ");
      for(k=0;k<5;k++) 
      {
         kt_nutnhan();
         ht_glcd();
      }
      ht_lcd();
   }
   else if(cd==3)
   {
      lcd_goto(14,0);
      lcd_data("      ");
      lcd_goto(14,1);
      lcd_data("      ");
      for(k=0;k<5;k++) 
      {
         kt_nutnhan();
         ht_glcd();
      }
      ht_lcd();
   }
   else if(cd==4)
   {
      lcd_goto(0,2);
      lcd_data("      ");
      lcd_goto(0,3);
      lcd_data("      ");
      for(k=0;k<5;k++) 
      {
         kt_nutnhan();
         ht_glcd();
      }
      ht_lcd();
   }
   else 
   {
      ht_lcd();
      ht_glcd();
   }
}
void main()
{
   system_init();
   glcd_setup();
   lcd_setup();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   glcd_text_setup(72,10,2,1,1);
   glcd_text(':');
   glcd_text_setup(110,10,2,1,1);
   glcd_text(':');
   glcd_update();
   while(true)
   {
      kt_nutnhan();
      nhapnhay();
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
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
