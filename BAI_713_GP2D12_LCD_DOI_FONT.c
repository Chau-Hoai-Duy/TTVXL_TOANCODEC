#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
unsigned int16 distance=0,kccu=0;
void main()
{
   system_init();
   lcd_setup();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   while(true)
   {
      set_adc_channel(gp2d12_channel); delay_us(20);
      distance = read_adc();
      distance =pow(4277/distance,1.115);
      if (distance>80) distance=80;
      else if(distance<10) distance=10;
      if(distance<30)
      {
         if(distance!=kccu)
         {
            lcd_write_4x3_num(10,7);
            lcd_write_4x3_num(10,10);
            lcd_goto(9,0);
            lcd_data(distance/10%10+48);
            lcd_data(distance%10+48);
            kccu=distance;
         }
      }
      else if((distance>=30)&&(distance<50))
      {
         if(distance!=kccu)
         {
            lcd_write_4x3_num(10,7);
            lcd_write_4x3_num(10,10);
            lcd_goto(9,0);
            lcd_data("  ");
            lcd_write_2x3_num(distance/10%10,7,1);
            lcd_write_2x3_num(distance%10,10,1);
            kccu=distance;
         }
      }
      else
      { 
         if(distance!=kccu)
         {
            lcd_write_2x3_num(10,7,1);
            lcd_write_2x3_num(10,10,1);
            lcd_write_4x3_num(distance/10%10,7);
            lcd_write_4x3_num(distance%10,10);
            kccu=distance;
         }
      }
   }
}
