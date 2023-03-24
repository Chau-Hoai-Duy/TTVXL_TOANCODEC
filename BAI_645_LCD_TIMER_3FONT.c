#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
signed int8 bdn=0,giay=0,phut=0,gio=0,cd=0,font=0;
unsigned int16 k;
void kt_nutnhan()
{
   if(inputcd(inv)==0)
   {
      font++;
      if(font>=3) font=0;
      if(font==1)
      {
         lcd_goto(0,0);
         lcd_data("                    ");
      }
      if(font==2)
      {
         lcd_goto(0,1);
         lcd_data("                    ");
         lcd_goto(0,2);
         lcd_data("                    ");
      }
      if(font==0)
      {
         lcd_goto(0,1);
         lcd_data("                    ");
         lcd_goto(0,2);
         lcd_data("                    ");
         lcd_goto(0,0);
         lcd_data("                    ");
         lcd_goto(0,3);
         lcd_data("                    ");
      }
   }
   if(inputcd(mod)==0)
   {
      cd++;
      if(cd>=4) cd=0;
   }
   if(inputcd(up)==0)
   {
      if(cd==1) 
      {
         giay++;
         if(giay>=60) giay=0;
      }
      else if(cd==2) 
      {
         phut++;
         if(phut>=60) phut=0;
      }
      else if(cd==3) 
      {
         gio++;
         if(gio>=13) gio=1;
      }
   }
      if(inputcd(dw)==0)
      {
         if(cd==1) 
         {
            giay--;
            if(giay<0) giay=59;
         }
         else if(cd==2) 
         {
            phut--;
            if(phut<0) phut=59;
         }
         else if(cd==3) 
         {
            gio--;
            if(gio<=0) gio=12;
         }
      }
}
void main()
{
   system_init();
   lcd_setup();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while(true)
   { 
        kt_nutnhan();
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
        /***************************************khong chinh gi***************************/
        if(cd==0)
        {
           if(font==0)
           {
              lcd_goto(5,0);
              printf(lcd_data,"%02u",gio);
              lcd_data(':');
              printf(lcd_data,"%02u",phut);
              lcd_data(':');
              printf(lcd_data,"%02u",giay);
           }
           if(font==1)
           {
              lcd_write_2x3_num(gio/10%10,0,1);
              lcd_write_2x3_num(gio%10,3,1);
              lcd_write_2x3_num(phut/10%10,7,1);
              lcd_write_2x3_num(phut%10,10,1);
              lcd_write_2x3_num(giay/10%10,14,1);
              lcd_write_2x3_num(giay%10,17,1);
           }
           if(font==2)
           {
              lcd_write_4x3_num(gio/10%10,0);
              lcd_write_4x3_num(gio%10,3);
              lcd_write_4x3_num(phut/10%10,7);
              lcd_write_4x3_num(phut%10,10);
              lcd_write_4x3_num(giay/10%10,14);
              lcd_write_4x3_num(giay%10,17);
           }
        }
        /***********************************CHINH GIO***************************/
        if(cd==3)
        {
            if(font==0)
            {
               lcd_goto(8,0);
               printf(lcd_data,"%02u",phut);
               lcd_goto(11,0);
               printf(lcd_data,"%02u",giay);
            }
            if(font==1)
            {
               lcd_write_2x3_num(phut/10%10,7,1);
               lcd_write_2x3_num(phut%10,10,1);
               lcd_write_2x3_num(giay/10%10,14,1);
               lcd_write_2x3_num(giay%10,17,1);
            }
            if(font==2)
            {
               lcd_write_4x3_num(phut/10%10,7);
               lcd_write_4x3_num(phut%10,10);
               lcd_write_4x3_num(giay/10%10,14);
               lcd_write_4x3_num(giay%10,17);
            }
            if(k<100)
            {
               if(font==0)
               {
                  lcd_goto(5,0);
                  lcd_data("  ");
                  k++;
               }
               if(font==1)
               {
                  lcd_goto(0,1);
                  lcd_data("      ");
                  lcd_goto(0,2);
                  lcd_data("      ");
                  k++;
               }
               if(font==2)
               {
                  lcd_goto(0,0);
                  lcd_data("      ");
                  lcd_goto(0,1);
                  lcd_data("      ");
                  lcd_goto(0,2);
                  lcd_data("      ");
                  lcd_goto(0,3);
                  lcd_data("      ");
                  k++;
               }
            }
            else if(k<200)
            {
               if(font==0)
               {
                  lcd_goto(5,0);
                  printf(lcd_data,"%02u",gio);
                  k++;
               }
               if(font==1)
               {
                  lcd_write_2x3_num(gio/10%10,0,1);
                  lcd_write_2x3_num(gio%10,3,1);
                  k++;
               }
               if(font==2)
               {
                  lcd_write_4x3_num(gio/10%10,0);
                  lcd_write_4x3_num(gio%10,3);
                  k++;
               }
            }
            else k=0;
        }
        /*****************************CHINH PHUT*****************************************/
        else if(cd==2)
        {
            if(font==0)
            {
               lcd_goto(11,0);
               printf(lcd_data,"%02u",giay);
            }
            if(font==1)
            {
               lcd_write_2x3_num(giay/10%10,14,1);
               lcd_write_2x3_num(giay%10,17,1);
            }
            if(font==2)
            {
               lcd_write_4x3_num(giay/10%10,14);
               lcd_write_4x3_num(giay%10,17);
            }
            if(k<100)
            {
               if(font==0)
               {
                  lcd_goto(8,0);
                  lcd_data("  ");
                  k++;
               }
               if(font==1)
               {
                  lcd_goto(7,1);
                  lcd_data("      ");
                  lcd_goto(7,2);
                  lcd_data("      ");
                  k++;
               }
               if(font==2)
               {
                  lcd_goto(7,0);
                  lcd_data("      ");
                  lcd_goto(7,1);
                  lcd_data("      ");
                  lcd_goto(7,2);
                  lcd_data("      ");
                  lcd_goto(7,3);
                  lcd_data("      ");
                  k++;
               }
            }
            else if(k<200)
            {
               if(font==0)
               {
                  lcd_goto(8,0);
                  printf(lcd_data,"%02u",phut);
                  k++;
               }
               if(font==1)
               {
                  lcd_write_2x3_num(phut/10%10,7,1);
                  lcd_write_2x3_num(phut%10,10,1);
                  k++;
               }
               if(font==2)
               {
                  lcd_write_4x3_num(phut/10%10,7);
                  lcd_write_4x3_num(phut%10,10);
                  k++;
               }
            }
            else k=0;
        }
        /***************************CHINH GIAY*************************************/
        else if(cd==1)
        {
            if(k<100)
            {
               if(font==0)
               {
                  lcd_goto(11,0);
                  lcd_data("  ");
                  k++;
               }
               if(font==1)
               {
                  lcd_goto(14,1);
                  lcd_data("      ");
                  lcd_goto(14,2);
                  lcd_data("      ");
                  k++;
               }
               if(font==2)
               {
                  lcd_goto(14,0);
                  lcd_data("      ");
                  lcd_goto(14,1);
                  lcd_data("      ");
                  lcd_goto(14,2);
                  lcd_data("      ");
                  lcd_goto(14,3);
                  lcd_data("      ");
                  k++;
               }
            }
            else if(k<200)
            {
               if(font==0)
               {
                  lcd_goto(11,0);
                  printf(lcd_data,"%02u",giay);
                  k++;
               }
               if(font==1)
               {
                  lcd_write_2x3_num(giay/10%10,14,1);
                  lcd_write_2x3_num(giay%10,17,1);
                  k++;
               }
               if(font==2)
               {
                  lcd_write_4x3_num(giay/10%10,14);
                  lcd_write_4x3_num(giay%10,17);
                  k++;
               }
            }
            else k=0;
        }
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
