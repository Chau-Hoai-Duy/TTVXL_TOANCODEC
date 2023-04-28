
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
#include<tv_ds18b20.c>

unsigned int8 solan = 0, khoangcach = 0,tam = 0, adc = 0;
unsigned int16 tong;

unsigned int8 dpg = 9, tp = 0,tp_ht = 10;
int1 dpg_tp = 0;

unsigned int16 nguyen,thapphan,temp_cu=99;

void vehinh_glcd(){
   glcd_clear(0);
   
   // %9*15 + 4
   //9 -> 4
   //10 -> 19
   //11 -> 34
   //12 -> 49
   
   glcd_rect(4,(dpg%9)*15+4,65,(dpg%9)*15+12,1,1);
   glcd_text_setup(5,5,1,!(dpg == 9),1);
   glcd_text("DPG 9 BIT");
   glcd_text_setup(5,20,1,!(dpg == 10),1);
   glcd_text("DPG 10 BIT");
   glcd_text_setup(5,35,1,!(dpg == 11),1);
   glcd_text("DPG 11 BIT");
   glcd_text_setup(5,50,1,!(dpg == 12),1);
   glcd_text("DPG 12 BIT");
   
   // 0 -> 4
   // 1 -> 19
   // 2 -> 34
   
   glcd_rect(79,tp*15+4,125,tp*15+12,1,1);
   glcd_text_setup(80,5,1,!(tp == 0),1);
   glcd_text("1 SO TP");
   glcd_text_setup(80,20,1,!(tp == 1),1);
   glcd_text("2 SO TP");
   glcd_text_setup(80,35,1,!(tp == 2),1);
   glcd_text("3 SO TP");
   
   glcd_update();
}

void kt_nn(){
   if(!inputcd(UP)){
      if(dpg_tp == 0) {
         if(dpg < 12)dpg++;
         ds18b20_set_resolution(dpg);
      }
      else if(tp  < 2)tp++;
      vehinh_glcd();
   }
   if(!inputcd(DW)){
      if(dpg_tp == 0) {
         if(dpg > 9)dpg--;
         ds18b20_set_resolution(dpg);   
      }
      else            if(tp  > 0)tp--;
      vehinh_glcd();
   }
   if(!inputcd(MOD)) dpg_tp = !dpg_tp;
}

void main(){
   system_init();
   
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(analog_pins|VSS_VDD);
   set_adc_channel(gp2d12_channel);
   delay_us(20);
   
   ds18b20_set_resolution(9);
   lcd_setup();
   glcd_setup();
   
   
   lcd_goto(10,2); 
   lcd_data(0xdf);
   lcd_data(0); lcd_data(1); lcd_data(1);
   lcd_goto(11,3);
   lcd_data(5); lcd_data(3); lcd_data(3);
   vehinh_glcd();
   while(true){
      kt_nn();
         
      adc = read_adc();
   
      tam = pow(4277 / adc,1.115);
      if(tam > 80)tam = 80;
      else if(tam < 10)tam = 10;
      
      tong += tam;
      
      if(solan == 9){
         khoangcach = tong/10;
         tong = 0; solan = 0;
         
         s7seg.led[0] = m7d[khoangcach%10];
         s7seg.led[1] = m7d[khoangcach/10];
         s7seg_display();
      }else solan++;
      
      if(ds18b20_read_temperature() == OK){
         if(ds18b20.temperatureA != temp_cu){
            nguyen = ds18b20.temperatureA>>4;
            lcd_write_2x3_num(nguyen/10,0,2);
            lcd_write_2x3_num(nguyen%10,3,2);
            if(tp == 0) {
               thapphan = (ds18b20.temperatureA&0x0f)*10/16;
               printf(lcd_data,".%01lu  ",thapphan);  
            }
            else if(tp == 1){
               thapphan = (ds18b20.temperatureA&0x0f)*100/16;
               printf(lcd_data,".%02lu  ",thapphan); 
            }
            else if(tp == 2){
               thapphan = (ds18b20.temperatureA&0x0f)*1000/16;
               printf(lcd_data,".%03lu ",thapphan); 
            }
            temp_cu = ds18b20.temperatureA;
         }
      }
   }
}

