#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
unsigned int16 lm351=0,lm352=0,i, tong=0;
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("LM35A:");
   lcd_goto(0,2);
   lcd_data("LM35B:");
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_TO_AN2|VSS_VDD);
   while(true)
   {
      set_adc_channel(0); delay_us(20);
      tong=0;
      for(i=0;i<100;i++)
      {
         tong=tong+read_adc()/2.046;
         delay_ms(1);
      }
      lm351=tong/100;
      set_adc_channel(1); delay_us(20);
      tong=0;
      for(i=0;i<100;i++)
      {
         tong=tong+read_adc()/2.046;
         delay_ms(1);
      }
      lm352=tong/100;
      /*************************************Xu ly bat bong den*************************************/
      if((lm351>40)||(lm352>40))
      {
         led32.ledx1[0]=1;
         triac_2_off();
      }
      else if((lm351<35)&&(lm352<35))
      {
         triac_2_on();
      }
      else led32.ledx1[0]=0;
      /***************************************Xu ly hien thi***************************************/
      lcd_write_2x3_num(lm351/10%10,14,0);
      lcd_write_2x3_num(lm351%10,17,0);
      lcd_write_2x3_num(lm352/10%10,14,2);
      lcd_write_2x3_num(lm352%10,17,2);
      d7seg.led[0]=m7d[lm351%10];
      d7seg.led[1]=m7d[lm351/10%10];
      d7seg.led[2]=m7d[lm352%10]-128;
      d7seg.led[3]=m7d[lm352/10%10];
      led32_display();
      d7seg_display();
   }
}
