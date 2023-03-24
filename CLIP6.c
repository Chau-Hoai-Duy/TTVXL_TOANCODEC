#include<tv_boards.c>
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
         lcd_goto(0,3);
         lcd_data("                    ");
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
void nhapnhay()
{
   if(cd==1)
   {
      lcd_goto(6,1);
      lcd_data("  ");
      lcd_goto(0,3);
      lcd_data("CHINH GIO");
      for(k=0;k<500;k++) kt_nutnhan();
   }
   if(cd==2)
   {
      lcd_goto(9,1);
      lcd_data("  ");
      lcd_goto(0,3);
      lcd_data("CHINH PHUT");
      for(k=0;k<500;k++) kt_nutnhan();
   }
   if(cd==3)
   {
      lcd_goto(12,1);
      lcd_data("  ");
      lcd_goto(0,3);
      lcd_data("CHINH GIAY");
      for(k=0;k<500;k++) kt_nutnhan();
   }
   if(cd==4)
   {
      lcd_goto(0,2);
      lcd_data("  ");
      lcd_goto(0,3);
      lcd_data("CAI GIOI HAN SP");
      for(k=0;k<200;k++) kt_nutnhan();
   }
}
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(6,0);
   lcd_data("20142157");
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
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
      /*********************************xu li hien thi*****************************/
      lcd_goto(6,1);
      lcd_data(gio/10%10+48);
      lcd_data(gio%10+48);
      lcd_data(':');
      lcd_data(phut/10%10+48);
      lcd_data(phut%10+48);
      lcd_data(':');
      lcd_data(giay/10%10+48);
      lcd_data(giay%10+48);
      lcd_goto(0,2);
      lcd_data(gt_spcai/10%10+48);
      lcd_data(gt_spcai%10+48);
      lcd_goto(18,2);
      lcd_data(dem/10%10+48);
      lcd_data(dem%10+48);
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
