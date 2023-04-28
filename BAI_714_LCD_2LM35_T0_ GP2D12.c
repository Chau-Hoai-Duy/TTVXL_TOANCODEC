#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#define solan 50
unsigned int16 kc=0,kccu=0, tonga=0, tongb=0,lm35a=0,lm35b=0, T0;
unsigned int8 n=0;
void main()
{
   system_init();
   lcd_setup();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1| T0_8_BIT);
   set_timer0(0);
   lcd_goto(0,0);
   lcd_data("LM35A:");
   lcd_goto(10,0);
   lcd_data("LM35B:");
   lcd_goto(0,1);
   lcd_data("SAN PHAM:");
   lcd_goto(0,2);
   lcd_data("KHOANG CACH:");
   while(true)
   {
      /*************************************dem san pham********************************************/
      T0=get_timer0();
      /*********************************************do nhiet do*************************************/
      set_adc_channel(lm35a_channel); delay_us(20);
      tonga+=read_adc();
      set_adc_channel(lm35b_channel); delay_us(20);
      tongb+=read_adc();
      if(n>=solan)
      {
         lm35a=tonga/2.046/solan;
         lm35b=tongb/2.046/solan;
         n=0;
         tonga=0;
         tongb=0;
      }
      else n++;
      /*********************************************do khoang cach**********************************/
      set_adc_channel(gp2d12_channel); delay_us(20);
      kc = read_adc();
      kc =pow(4277/kc,1.115);
      if (kc>80) kc=80;
      else if(kc<10) kc=10;
      /**********************************HIEN THI LCD*********************************************/
      lcd_goto(6,0);
      lcd_data(lm35a/10%10+48);
      lcd_data(lm35a%10+48);
      lcd_goto(16,0);
      lcd_data(lm35b/10%10+48);
      lcd_data(lm35b%10+48);
      lcd_goto(9,1);
      lcd_data(T0/100%10+48);
      lcd_data(T0/10%10+48);
      lcd_data(T0%10+48);
      lcd_goto(12,2);
      lcd_data(kc/10%10+48);
      lcd_data(kc%10+48);
   }
}
