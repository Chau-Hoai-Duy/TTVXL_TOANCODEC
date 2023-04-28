#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
#include<tv_key4x4.c>
signed int8 i=0,k=0,hu=0;
void hieu_ung_led()
{
   //chop tat, hu=0
   if(hu==0)
      if(i<6)
      {
         led32.ledx32=~led32.ledx32;
         led32_display();
         delay_ms(500);
         i++;
      }
      else 
      {  
         i=0;
         hu++;
      }
      if(i<=32)
      {
         led32.ledx32=~(0xffffffff<<i);
         led32_display();
         delay_ms(500);
      }
}
void main()
{
   system_init();
   while(true)
   {
      hieu_ung_led();
   }
}
