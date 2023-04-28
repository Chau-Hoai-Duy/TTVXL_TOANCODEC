//#DEFINE BOARD D501
#include<tv_boards.c>
unsigned int16 lm351=0,lm352=0,i, tonga=0, tongb=0;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins| VSS_VDD);
   while(true)
   {
      set_adc_channel(lm35a_channel); delay_us(20);
      for(i=0;i<100;i++)
      {
         tonga=tonga+read_adc()/2.046;
      }
      lm351=tonga/100;
      set_adc_channel(lm35b_channel); delay_us(20);
      for(i=0;i<100;i++)
      {
         tongb=tongb+read_adc()/2.046;
      }
      lm352=tongb/100;
      d7seg.led[0]=m7d[lm351%10];
      d7seg.led[1]=m7d[lm351/10%10];
      d7seg.led[2]=m7d[lm352%10]-128;
      d7seg.led[3]=m7d[lm352/10%10];
      d7seg_display();
      tonga=0;
      tongb=0;
   }
}
//!#define solan 100
//!unsigned int16 tonga=0,tongb=0;
//!unsigned int8 n=0,lm35a,lm35b;
//!void main()
//!{
//! system_init(); 
//! setup_adc(adc_clock_div_32);
//! setup_adc_ports(analog_pins|vss_vdd);
//! while(true)
//! { // Ðo LM35A
//! set_adc_channel(lm35a_channel); delay_us(20);
//! tonga += read_adc();
//! // Ðo LM35B
//! set_adc_channel(lm35b_channel); delay_us(20);
//! tongb += read_adc();
//! // Ð? s? l?n r?i thì tính toán ra nhi?t d?
//! if(n==solan)
//! {
//! lm35a= tonga/2.046/solan;
//! lm35b= tongb/2.046/solan;
//! tonga=0; tongb=0; n=0;
//! }else n++; 
//! d7seg.led[1]=m7d[lm35a/10%10];
//! d7seg.led[0]=m7d[lm35a%10]; 
//! d7seg.led[3]=m7d[lm35b/10%10];
//! d7seg.led[2]=m7d[lm35b%10]-128; // -128 d? xu?t hi?n d?u ch?m
//! d7seg_display(); 
//! }
//!}
