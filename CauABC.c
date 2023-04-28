//#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
#include<tv_key4x4.c>
signed int8 T0,T0_TAM=0, chuc=0;
unsigned int1 cd=0,xoa0vn=0;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key==0x0d)
      {
         cd=~cd;
         if(cd==0)
         {
            s7seg.led[7]=m7d[T0/10%10];
            s7seg.led[6]=m7d[T0%10];
            s7seg.led[0]=0xff-1-2-4-8;
            s7seg.led[1]=m7d[1];
            s7seg.led[2]=m7d[10];
            s7seg.led[3]=m7d[12];
            s7seg.led[4]=0xff-1-32-16-8;
            lcd_goto(4,1);
            lcd_data("      ");
            lcd_goto(4,2);
            lcd_data("      ");
            lcd_goto(11,2);
            lcd_data("     ");
         }
         if(cd==1)
         {
            s7seg.led[7]=0xff;
            s7seg.led[6]=0xff;
            s7seg.led[0]=0xff;
            s7seg.led[1]=0xff;
            s7seg.led[2]=0xff;
            s7seg.led[3]=0xff;
            s7seg.led[4]=0xff;
            lcd_write_2x3_num(T0/10%10,4,1);
            lcd_write_2x3_num(T0%10,7,1);
            lcd_goto(11,2);
            lcd_data("(CAI)");
         }
         if(xoa0vn==0)
         {
            lcd_goto(0,0);
            lcd_data("BAT 0 VN");
            if(cd==0)
            {
               s7seg.led[7]=m7d[T0/10%10];
            }
            if(cd==1)
            {
               lcd_write_2x3_num(T0/10%10,4,1);
            }
         }
         else if(xoa0vn==1)
         {
            lcd_goto(0,0);
            lcd_data("XOA 0 VN");
            if(T0/10%10==0)
            {
               if(cd==0)
               {
                  s7seg.led[7]=0xff;
               }
               if(cd==1)
               {
                  lcd_write_2x3_num(10,4,1);
               }
            }
         }
      }
      /*********************************xoa so 0 vo nghia*********************************/
      if(key4x4.key==0x0a)
      {
         xoa0vn=~xoa0vn;
         if(xoa0vn==0)
         {
            lcd_goto(0,0);
            lcd_data("BAT 0 VN");
            if(cd==0)
            {
               s7seg.led[7]=m7d[T0/10%10];
            }
            if(cd==1)
            {
               lcd_write_2x3_num(T0/10%10,4,1);
            }
         }
         else if(xoa0vn==1)
         {
            lcd_goto(0,0);
            lcd_data("XOA 0 VN");
            if(T0/10%10==0)
            {
               if(cd==0)
               {
                  s7seg.led[7]=0xff;
               }
               if(cd==1)
               {
                  lcd_write_2x3_num(10,4,1);
               }
            }
         }
      }
   }
}
void main()
{
   system_init();
   s7seg.led[0]=0xff-1-2-4-8;
   s7seg.led[1]=m7d[1];
   s7seg.led[2]=m7d[10];
   s7seg.led[3]=m7d[12];
   s7seg.led[4]=0xff-1-32-16-8;
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("BAT 0 VN");
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(6);
   while(true)
   {
      kt_nutnhan();
      /**************************************xu li dem sn pham******************************************/
      T0=get_timer0();
      if(cd==0)
      {
         if(T0!=T0_TAM)
         {
            if(xoa0vn==0)
            {
               s7seg.led[7]=m7d[T0/10%10];
               s7seg.led[6]=m7d[T0%10];
               s7seg.led[0]=0xff-1-2-4-8;
               s7seg.led[1]=m7d[1];
               s7seg.led[2]=m7d[10];
               s7seg.led[3]=m7d[12];
               s7seg.led[4]=0xff-1-32-16-8;
               lcd_goto(4,1);
               lcd_data("      ");
               lcd_goto(4,2);
               lcd_data("      ");
               lcd_goto(11,2);
               lcd_data("     ");
            }
            else if(xoa0vn==1)
            {
               if(T0/10%10==0)
               {
                  s7seg.led[7]=0xff;
                  s7seg.led[6]=m7d[T0%10];
                  s7seg.led[0]=0xff-1-2-4-8;
                  s7seg.led[1]=m7d[1];
                  s7seg.led[2]=m7d[10];
                  s7seg.led[3]=m7d[12];
                  s7seg.led[4]=0xff-1-32-16-8;
                  lcd_goto(4,1);
                  lcd_data("      ");
                  lcd_goto(4,2);
                  lcd_data("      ");
                  lcd_goto(11,2);
                  lcd_data("     ");
               }
               else
               {
                  s7seg.led[7]=m7d[T0/10%10];
                  s7seg.led[6]=m7d[T0%10];
                  s7seg.led[0]=0xff-1-2-4-8;
                  s7seg.led[1]=m7d[1];
                  s7seg.led[2]=m7d[10];
                  s7seg.led[3]=m7d[12];
                  s7seg.led[4]=0xff-1-32-16-8;
                  lcd_goto(4,1);
                  lcd_data("      ");
                  lcd_goto(4,2);
                  lcd_data("      ");
                  lcd_goto(11,2);
                  lcd_data("     ");
               }
            }
            T0_TAM=T0;
            if(T0>=14) set_timer0(7);
         }
      }
      else if(cd==1)
      {
         if(T0!=T0_TAM)
         {
            if(xoa0vn==0)
            {
               s7seg.led[7]=0xff;
               s7seg.led[6]=0xff;
               s7seg.led[0]=0xff;
               s7seg.led[1]=0xff;
               s7seg.led[2]=0xff;
               s7seg.led[3]=0xff;
               s7seg.led[4]=0xff;
               lcd_write_2x3_num(T0/10%10,4,1);
               lcd_write_2x3_num(T0%10,7,1);
               lcd_goto(11,2);
               lcd_data("(CAI)");
            }
            else if(xoa0vn==1)
            {
               if(T0/10%10==0)
               {
                    lcd_write_2x3_num(10,4,1);
                    lcd_write_2x3_num(T0%10,7,1);
                    s7seg.led[7]=0xff;
                    s7seg.led[6]=0xff;
                    s7seg.led[0]=0xff;
                    s7seg.led[1]=0xff;
                    s7seg.led[2]=0xff;
                    s7seg.led[3]=0xff;
                    s7seg.led[4]=0xff;
               }
               else  
               {
                  lcd_write_2x3_num(T0/10%10,4,1);
                  lcd_write_2x3_num(T0%10,7,1);
                  s7seg.led[7]=0xff;
                  s7seg.led[6]=0xff;
                  s7seg.led[0]=0xff;
                  s7seg.led[1]=0xff;
                  s7seg.led[2]=0xff;
                  s7seg.led[3]=0xff;
                  s7seg.led[4]=0xff;
               }
            }
            T0_TAM=T0;
            if(T0>=14) set_timer0(7);
         }
      }
      s7seg_display();
   }
}
