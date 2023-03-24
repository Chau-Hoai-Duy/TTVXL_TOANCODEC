#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
const unsigned int8 traitim[]={0x00,0x0A,0x15,0x11,0x0A,0x04,0x00,0x00};
unsigned int8 n,i;
void main()
{
   system_init();
   lcd_setup();
   lcd_command(0x40);
   for(n=0;n<8;n++) lcd_data(traitim[n]);
   lcd_goto(0,0);
   lcd_data("HIEN THI TRAI TIM");
   lcd_goto(0,1);
   for(i=0;i<20;i++)
   {
      lcd_data(0);
   }
   while(true)
   {
   }
}
