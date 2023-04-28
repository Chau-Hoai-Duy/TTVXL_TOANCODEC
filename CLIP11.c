#define board D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
unsigned int8 gio=0, phut=0, giay=0, bdn=0;
unsigned int8 sp=0, spcu=0;
void main()
{
   system_init();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("SAN PHAM:");
   printf(lcd_data,"%02u",sp);
   while(true)
   {
      /**************************************xu li dem giay timer1**************************/
      if(bdn>=10)
      {
         bdn-=10;
         giay++;
         if(giay>=60)
         {
            giay=0;
            phut++;
            if(phut>=60)
            {
               phut=0;
               gio++;
               if(gio>=13)
               gio=1;
            }
         }
      }
      /**********************************dem sp*******************************************/
      sp=get_timer0();
      if(sp!=spcu)
      {
         if(sp>=21) set_timer0(1);
         lcd_goto(9,0);
         printf(lcd_data,"%02u",sp);
         spcu=sp;
      }
      /************************************do nhiet do************************************/
      
      /*********************************xu li hien thi************************************/
      s7seg.led[7]=m7d[gio/10%10];
      s7seg.led[6]=m7d[gio%10];
      s7seg.led[5]=0xff-64;
      s7seg.led[4]=m7d[phut/10%10];
      s7seg.led[3]=m7d[phut%10];
      s7seg.led[2]=0xff-64;
      s7seg.led[1]=m7d[giay/10%10];
      s7seg.led[0]=m7d[giay%10];
      s7seg_display();
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
