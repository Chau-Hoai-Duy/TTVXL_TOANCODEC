#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_key4x4.c>
unsigned int8 RONG0[]="                   ";
unsigned int8 RONG1[]="                   ";
unsigned int8 RONG2[]="                   ";
unsigned int8 RONG3[]="                   ";
unsigned int8 i=0,j=0,dem=0;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key<10) 
      {
         RONG0[19]=key4x4.key+0x30;
         RONG1[19]=RONG0[0];
         RONG2[19]=RONG1[0];
         RONG3[19]=RONG2[0];
      }
      else 
      {
         RONG0[19]=key4x4.key+0x37;
         RONG1[19]=RONG0[0];
         RONG2[19]=RONG1[0];
         RONG3[19]=RONG2[0];
      }
      for(i=0;i<19;i++) 
      {
         RONG0[i]=RONG0[i+1];
         RONG1[i]=RONG1[i+1];
         RONG2[i]=RONG2[i+1];
         RONG3[i]=RONG3[i+1];
      }
         lcd_goto(0,0);
         for(j=0;j<19;j++) lcd_data(RONG0[j]);
         lcd_goto(0,1);
         for(j=0;j<19;j++) lcd_data(RONG1[j]);
         lcd_goto(0,2);
         for(j=0;j<19;j++) lcd_data(RONG2[j]);
         lcd_goto(0,3);
         for(j=0;j<19;j++) lcd_data(RONG3[j]);
   }
}
void main()
{
   system_init();
   lcd_setup();
   while(true)
   {
      kt_nutnhan();
   }
}
