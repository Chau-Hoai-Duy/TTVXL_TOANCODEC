#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
#include<tv_key4x4.c>
signed int8 T0,T0_TAM=0;
unsigned int1 cd=0;
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
            T0_TAM=T0;
            if(T0>=14) set_timer0(7);
         }
      }
      else if(cd==1)
      {
         if(T0!=T0_TAM)
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
            T0_TAM=T0;
            if(T0>=14) set_timer0(7);
         }
      }
      s7seg_display();
   }
}
