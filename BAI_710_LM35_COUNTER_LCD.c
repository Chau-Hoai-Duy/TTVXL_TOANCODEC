#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#define solan 100
unsigned int16 lm351=0,lm352=0,dem=0,i=0, tong1=0,tong2=0;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_TO_AN2|VSS_VDD);
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("NHIET DO LM35A:");
   lcd_goto(0,1);
   lcd_data("NHIET DO LM35B:");
   lcd_goto(0,2);
   lcd_data("DEM SAN PHAM:");
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   while(true)
   {
      dem=get_timer0();
      if(dem>=100) set_timer0(1);
      set_adc_channel(0);
      tong1+=read_adc()/2.046;
      set_adc_channel(1);
      tong2+=read_adc()/2.046;
      if(i>=solan)
      {
         lm351=tong1/100; lm352=tong2/100;
         tong1=0;tong2=0;i=0;
      }
      else i++;
      if(lm351>40||lm352>40)
      {
         triac_2_off();
         led32.ledx1[0]=1;
      }
      else if((lm351<35)&&(lm352<35)) triac_2_on();
      else led32.ledx1[0]=0;
      led32_display();
      /********************************xu ly hien thi*****************************/
      lcd_goto(15,0);
      lcd_data(lm351/10%10+48);
      lcd_data(lm351%10+48);
      lcd_goto(15,1);
      lcd_data(lm352/10%10+48);
      lcd_data(lm352%10+48);
      lcd_goto(13,2);
      lcd_data(dem/10%10+48);
      lcd_data(dem%10+48);
   }
}
