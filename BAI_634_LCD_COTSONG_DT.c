#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
const unsigned int8 cotsong[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,                                          
0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x14,                                          
0x00,0x00,0x00,0x00,0x00,0x01,0x05,0x15,                                          
0x01,0x00,0x00,0x00,0x08,0x08,0x08,0x08,                                                                                    
0x01,0x00,0x00,0x02,0x0A,0x0A,0x0A,0x0A,                                                                                  
0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,                                          
0x00,0x04,0x14,0x14,0x14,0x14,0x14,0x14,                                          
0x01,0x05,0x15,0x15,0x15,0x15,0x15,0x15                                                                   
};
unsigned int8 n,i;
void main()
{
   system_init();
   lcd_setup();
   lcd_command(0x40);
   for(n=0;n<64;n++) lcd_data(cotsong[n]);
   lcd_goto(0,0);
   lcd_data("SONG DIEN THOAI");
   while(true)
   {
      for(i=0;i<8;i++)
      {
         if(i<3)
         {
            lcd_goto(0,1);
            lcd_data(i);
         }
         else if((i>=3)&&(i<5))
         {
            lcd_goto(1,1);
            lcd_data(i);
         }
         else if(i>=5)
         {
            lcd_goto(2,1);
            lcd_data(i);
         }
         delay_ms(500);
      }
      lcd_goto(0,1);
      lcd_data("   ");
   }
}
