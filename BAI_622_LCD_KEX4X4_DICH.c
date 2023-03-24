#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_key4x4.c>
unsigned int8 RONG[]="                   ";
unsigned int8 i=0,j=0;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key<10) RONG[19]=key4x4.key+0x30;
      else RONG[19]=key4x4.key+0x37;
      lcd_goto(0,1);
      for(i=0;i<19;i++) RONG[i]=RONG[i+1];
      for(j=0;j<19;j++) lcd_data(RONG[j]);
   }
}
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(3,0);
   lcd_data("HAY NHAN PHIM");
   while(true)
   {
      kt_nutnhan();
   }
}
