#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
signed int8 bdn=0,giay=0,phut=0,gio=0,cd=0;
unsigned int16 k;
void kt_nutnhan()
{
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
            if(giay<=0) giay=59;
         }
         else if(cd==2) 
         {
            phut--;
            if(phut<=0) phut=59;
         }
         else if(cd==3) 
         {
            gio--;
            if(gio<=0) gio=13;
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
        if(cd==0)
        {
           lcd_goto(5,0);
           printf(lcd_data,"%02u",gio);
           lcd_data(':');
           printf(lcd_data,"%02u",phut);
           lcd_data(':');
           printf(lcd_data,"%02u",giay);
           s7seg.led[7]=m7d[gio/10%10];
           s7seg.led[6]=m7d[gio%10];
           s7seg.led[5]=0xff-64;
           s7seg.led[4]=m7d[phut/10%10];
           s7seg.led[3]=m7d[phut%10];
           s7seg.led[2]=0xff-64;
           s7seg.led[1]=m7d[giay/10%10];
           s7seg.led[0]=m7d[giay%10];
           s7seg_display();
        }
        if(cd==3)
        {
            lcd_goto(8,0);
            printf(lcd_data,"%02u",phut);
            lcd_goto(11,0);
            printf(lcd_data,"%02u",giay);
            s7seg.led[4]=m7d[phut/10%10];
            s7seg.led[3]=m7d[phut%10];
            s7seg.led[1]=m7d[giay/10%10];
            s7seg.led[0]=m7d[giay%10];
            s7seg_display();
            if(k<10)
            {
               lcd_goto(5,0);
               lcd_data("  ");
               s7seg.led[7]=0xff;
               s7seg.led[6]=0xff;
               s7seg_display();
               k++;
            }
            else if(k<20)
            {
               lcd_goto(5,0);
               printf(lcd_data,"%02u",gio);
               s7seg.led[7]=m7d[gio/10%10];
               s7seg.led[6]=m7d[gio%10];
               s7seg_display();
               k++;
            }
            else k=0;
        }
        else if(cd==2)
        {
            lcd_goto(11,0);
            printf(lcd_data,"%02u",giay);
            s7seg.led[1]=m7d[giay/10%10];
            s7seg.led[0]=m7d[giay%10];
            s7seg_display();
            if(k<10)
            {
               lcd_goto(8,0);
               lcd_data("  ");
               s7seg.led[4]=0xff;
               s7seg.led[3]=0xff;
               s7seg_display();
               k++;
            }
            else if(k<20)
            {
               lcd_goto(8,0);
               printf(lcd_data,"%02u",phut);
               s7seg.led[4]=m7d[phut/10%10];
               s7seg.led[3]=m7d[phut%10];
               s7seg_display();
               k++;
            }
            else k=0;
        }
        else if(cd==1)
        {
            if(k<10)
            {
               lcd_goto(11,0);
               lcd_data("  ");
               s7seg.led[1]=0xff;
               s7seg.led[0]=0xff;
               s7seg_display();
               k++;
            }
            else if(k<20)
            {
               lcd_goto(11,0);
               printf(lcd_data,"%02u",giay);
               s7seg.led[1]=m7d[giay/10%10];
               s7seg.led[0]=m7d[giay%10];
               s7seg_display();
               k++;
            }
            else k=0;
        }
        else s7seg_display();
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
