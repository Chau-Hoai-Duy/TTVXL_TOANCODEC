#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
unsigned int8 bdn=0,giay=0,phut=0;
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
        if(bdn>=10)
        {
            bdn=bdn-10;
            giay++;
            if(giay>=60)
            {
               giay=0;
               phut++;
               if(phut>=60)   phut=0;
            }
        }
        lcd_goto(7,0);
        printf(lcd_data,"%02u",phut);
        lcd_data(':');
        printf(lcd_data,"%02u",giay);
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
