#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_key4x4.c>
unsigned int1 tt=0;
unsigned int8 tgcai=0,i=0,k;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key==10)
      {
         if(tgcai==0) tt=0;
         else tt=1;
      }
      if(key4x4.key<10)
      {
         tgcai=key4x4.key;
         lcd_goto(14,1);
         lcd_data(key4x4.key+48);
      }
   }
}
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("DIEU KHIEN BUZZER");
   lcd_goto(0,1);
   lcd_data("BUZZER:");
   lcd_goto(10,1);
   lcd_data(",TG:0");
   while(true)
   {
      kt_nutnhan();
      if(tt==0) 
      {
         buzzer_off();
         lcd_goto(7,1);
         lcd_data("OFF");
      }
      else
      {
         for(i=0;i<tgcai;i++)
         {
            buzzer_on();
            lcd_goto(7,1);
            lcd_data(" ON");
            for(k=0;k<100;k++) 
            {
               kt_nutnhan();
               delay_ms(10);
            }
         }
         tt=0;
      }
   }
}
