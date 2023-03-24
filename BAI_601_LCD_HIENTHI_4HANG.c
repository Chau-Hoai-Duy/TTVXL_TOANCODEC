#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(0,0); // Di chuy?n con tr? d?n c?t 0 hàng 0
   lcd_data("DAI HOC SPKT TPHCM");
   lcd_goto(0,1); // Di chuy?n con tr? d?n c?t 0 hàng 1
   lcd_data("KHOA DIEN - DIEN TU");
   lcd_goto(0,2); // Di chuy?n con tr? d?n c?t 0 hàng 2
   lcd_data("BO MON DTCN-YS");
   lcd_goto(0,3); // Di chuy?n con tr? d?n c?t 0 hàng 3
   lcd_data("TTVXL MOUDLE LCD");
   while(true)
   { 
   }
}
