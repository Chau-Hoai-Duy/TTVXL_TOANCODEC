#define board D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
#include<tv_ds18b20.c>
unsigned int1 mode=1;
unsigned int8 reso=0, dec=0,n=1;
unsigned int16 tong=0, kc=0, ng, tp;
void ve_giaodien()
{ 
   glcd_clear(0);
   glcd_rect(0,reso*15,68,reso*15+15,1,1);
   glcd_rect(72, dec*15,125,dec*15+15,1,1);
   glcd_text_setup(3,4,1,reso!=0,1);
   glcd_text("DPG 9 BIT");
   glcd_text_setup(3,19,1,reso!=1,1);
   glcd_text("DPG 10 BIT");
   glcd_text_setup(3,34,1,reso!=2,1);
   glcd_text("DPG 11 BIT");
   glcd_text_setup(3,49,1,reso!=3,1);
   glcd_text("DPG 12 BIT");
   glcd_text_setup(75,4,1,dec!=0,1);
   glcd_text("1 SO TP");
   glcd_text_setup(75,19,1,dec!=1,1);
   glcd_text("2 SO TP");
   glcd_text_setup(75,34,1,dec!=2,1);
   glcd_text("3 SO TP");
   glcd_update();
}
void main()
{
   system_init();
   glcd_setup();
   lcd_setup();
   glcd_rect(0, reso*15,68,reso*15+15,1,1);
   glcd_rect(72, dec*15,125,dec*15+15,1,1);
   glcd_text_setup(3,4,1,reso!=0,1);
   glcd_text("DPG 9 BIT");
   glcd_text_setup(3,19,1,reso!=1,1);
   glcd_text("DPG 10 BIT");
   glcd_text_setup(3,34,1,reso!=2,1);
   glcd_text("DPG 11 BIT");
   glcd_text_setup(3,49,1,reso!=3,1);
   glcd_text("DPG 12 BIT");
   glcd_text_setup(75,4,1,dec!=0,1);
   glcd_text("1 SO TP");
   glcd_text_setup(75,19,1,dec!=1,1);
   glcd_text("2 SO TP");
   glcd_text_setup(75,34,1,dec!=2,1);
   glcd_text("3 SO TP");
   glcd_update();
   lcd_goto(0,0);
   lcd_data("DO NHIET DO");
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|Vss_Vdd);
   set_adc_channel(gp2d12_channel); delay_us(20);
   ds18b20_set_resolution(reso+9); delay_us(20);
   while(true)
   {
      if(inputcd(mod)==0) mode=~mode;
      if(mode==0)
      {
         if((inputcd(up)==0)&&(dec>0))
         {
            dec--;
            ve_giaodien();
         }
         if((inputcd(dw)==0)&&(dec<2))
         {
            dec++;
            ve_giaodien();
         }
      }
      if(mode==1)
      {
         if((inputcd(up)==0)&&(reso>0))
         {
            reso--;
            ve_giaodien();
            ds18b20_set_resolution(reso+9); delay_us(10);
         }
         if((inputcd(dw)==0)&&(reso<3))
         {
            reso++;
            ve_giaodien();
            ds18b20_set_resolution(reso+9); delay_us(10);
         }
      }
      /********************************************do nhiet do gp2d12 ****************************/
      tong+=pow(4277/read_adc(),1.115);
      if(n>=5)
      {
         kc=tong/5;
         tong=0;
         n=1;
      }
      else n++;
      s7seg.led[4]=m7d[kc/10%10];
      s7seg.led[3]=m7d[kc%10];
      s7seg_display();
      /*********************************do nhiet do DS18B20**************************************/
      if(ds18b20_read_temperature()==ok)
      {
         ng=ds18b20.temperatureA>>4;
         lcd_write_2x3_num(ng/10%10,8,2);
         lcd_write_2x3_num(ng%10,11,2);
         if(dec==0)
         {
            tp=(ds18b20.temperatureA&0x0f)*10/16;
            printf(lcd_data,".%01lu  ",tp);
         }
         if(dec==1)
         {
            tp=(ds18b20.temperatureA&0x0f)*100/16;
            printf(lcd_data,".%02lu ",tp);
         }
         if(dec==2)
         {
            tp=(ds18b20.temperatureA&0x0f)*1000/16;
            printf(lcd_data,".%03lu",tp);
         }
      }
   }
}
