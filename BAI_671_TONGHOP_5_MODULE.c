#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_glcd.c>
signed int8 sp=0,spcu=0,gio,phut,giay;
unsigned int8 i=0,cd=0,bdn;
unsigned int8 k;
void ht_7dquet()
{
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
void ht_lcd()
{
   lcd_write_2x3_num(sp/10%10,7,1);
   lcd_write_2x3_num(sp%10,10,1);
}
void ht_glcd()
{
   glcd_text_setup(85,15,2,1,1);
   printf(glcd_text,"%02u ",sp);
   glcd_update();
}
void ht_led7dtt()
{
   d7seg.led[1]=m7d[sp/10%10];
   d7seg.led[0]=m7d[sp%10];
   d7seg_display();
}
void delay()
{
   s7seg_display();
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
            if(gio>=13) gio=1;
         }
      }
   ht_7dquet();
   }
   sp=get_timer0();
   if(sp>=100) set_timer0(1);
   if(sp!=spcu)
   {
      ht_glcd();
      ht_lcd();
      ht_led7dtt();
      spcu=sp;
   }
}
void ht_32led()
{
   if(cd==0)
   {
      if(i<6)
      {
         led32.ledx32=~led32.ledx32;
         led32_display();
         for(k=0;k<10;k++) 
         {
            delay();
         }
         i++;
      }
      else
      {
         i=0;
         cd++;
      }
   }
   else if(cd==1)
   {
      if(i<=32)
      {
         led32.ledx32=~(0xffffffff<<i);
         led32_display();
         for(k=0;k<10;k++) 
         {
            delay();
         }
         i++;
      }
      else
      {
         i=0;
         cd++;
      }
   }
   else if(cd==2)
   {
      if(i<=32)
      {
         led32.ledx32=~(0xffffffff>>i);
         led32_display();
         for(k=0;k<10;k++) 
         {
            delay();
         }
         i++;
      }
      else 
      {
         i=0;
         cd++;
      }
   }
   else cd=0;
}
void main()
{
   system_init();
   lcd_setup();
   glcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   lcd_write_2x3_num(sp/10%10,7,1);
   lcd_write_2x3_num(sp%10,10,1);
   glcd_text_setup(85,15,2,1,1);
   printf(glcd_text,"%02u ",sp);
   glcd_update();
   d7seg.led[1]=m7d[sp/10%10];
   d7seg.led[0]=m7d[sp%10];
   d7seg_display();
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while(true)
   {
      ht_32led();
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
