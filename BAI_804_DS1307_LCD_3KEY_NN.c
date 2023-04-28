#define board D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_ds1307.c>
unsigned int8 mode=0,bdn=0;
unsigned int8 HieuchinhBCD(unsigned int8 x)
{
   if((x&0x0f)==0x0a) x+=6;
   if((x&0x0f)==0x0f) x-=6;
   return x;
}
void Hieuchinh_Napthoigian()
{
   ds1307.second=HieuchinhBCD(ds1307.second);
   ds1307.minute=HieuchinhBCD(ds1307.minute);
   ds1307.hour=HieuchinhBCD(ds1307.hour);
   ds1307.date=HieuchinhBCD(ds1307.date);
   ds1307.month=HieuchinhBCD(ds1307.month);
   ds1307.year=HieuchinhBCD(ds1307.year);
   ds1307_set_time(ds1307);
}
void kt_nutnhan()
{
   if(inputcd(mod)==0)
   {
      mode++;
      if(mode>=7) mode=0;
   }
   if(inputcd(up)==0)
   {
      if((mode==3)&&(ds1307.second<0x59)) ds1307.second++;
      if((mode==2)&&(ds1307.minute<0x59)) ds1307.minute++;
      if((mode==1)&&(ds1307.hour<0x23)) ds1307.hour++;
      if(mode==4&&ds1307.date<0x31) ds1307.date++;
      if(mode==5&&ds1307.month<0x12) ds1307.month++;
      if(mode==6&&ds1307.year<0x99) ds1307.year++;
      Hieuchinh_Napthoigian();
   }
   if(inputcd(dw)==0)
   {
      if((mode==3)&&(ds1307.second>0)) ds1307.second--;
      if((mode==2)&&(ds1307.minute>0)) ds1307.minute--;
      if((mode==1)&&(ds1307.hour>0)) ds1307.hour--;
      if((mode==4)&&(ds1307.date>0x01)) ds1307.date--;
      if((mode==5)&&(ds1307.month>0x01)) ds1307.month--;
      if(mode==6&&ds1307.year>0x01) ds1307.year--;
      Hieuchinh_Napthoigian();
   }
}
void nhapnhay()
{
   if(mode==1)
   {
      lcd_goto(0,1);
      lcd_data("  ");
   }
   else if(mode==2)
   {
      lcd_goto(3,1);
      lcd_data("  ");
   }
   else if(mode==3)
   {
      lcd_goto(6,1);
      lcd_data("  ");
   }
   else if(mode==4)
   {
      lcd_goto(12,1);
      lcd_data("  ");
   }
   else if(mode==5)
   {
      lcd_goto(15,1);
      lcd_data("  ");
   }
   else if(mode==6)
   {
      lcd_goto(18,1);
      lcd_data("  ");
   }
}
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(4,0);
   lcd_data("DS1307 CLOCK");
   if(ds1307_battery_check()==ERROR)
   {
      ds1307.second=0x00;
      ds1307.minute=0x00;
      ds1307.hour=0x00;
      ds1307_set_time(ds1307);
   }
   ds1307.date=0x18;
   ds1307.month=0x04;
   ds1307.year=0x23;
   ds1307_set_time(ds1307);
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while(true)
   {
      kt_nutnhan();
      if(bdn<5) nhapnhay();
      else if(bdn<10)
      {
         if(ds1307_read_time()==ok)
         {
            lcd_goto(0,1);
            printf(lcd_data,"%d%d:%d%d:%d%d",
                              ds1307.hour/16, ds1307.hour%16,
                              ds1307.minute/16, ds1307.minute%16,
                              ds1307.second/16, ds1307.second%16);
            lcd_goto(12,1);                  
            printf(lcd_data,"%d%d:%d%d:%d%d",
                              ds1307.date/16, ds1307.date%16,
                              ds1307.month/16, ds1307.month%16,
                              ds1307.year/16, ds1307.year%16);
         }
      }
      else bdn-=10;
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
