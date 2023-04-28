#define board D501
#include<tv_boards.c>
#include<tv_lcd.c>
#include<tv_ds1307.c>
unsigned int8 mode=0,bdn=0, phutcu=0, buzzer_on_time=0;
unsigned int8 gio=0, phut=0, giay=0, giocai=7, phutcai=0, giaycai=0;
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
      if(mode>=10) mode=0;
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
      if(mode==7&&giocai<23) giocai++;
      if(mode==8&&phutcai<59) phutcai++;
      if(mode==9&&giaycai<59) giaycai++;
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
      if(mode==7&&giocai>0) giocai--;
      if(mode==8&&phutcai>0) phutcai--;
      if(mode==9&&giaycai>0) giaycai--;
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
   else if(mode==7)
   {
      lcd_goto(8,2);
      lcd_data("  ");
   }
   else if(mode==8)
   {
      lcd_goto(11,2);
      lcd_data("  ");
   }
   else if(mode==9)
   {
      lcd_goto(14,2);
      lcd_data("  ");
   }
}
void chuyen_bcd_sang_dec()
{
   gio=ds1307.hour/16*10+ds1307.hour%16;
   phut=ds1307.minute/16*10+ds1307.minute%16;
   giay=ds1307.second/16*10+ds1307.second%16;
}
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(4,0);
   lcd_data("DS1307 CLOCK");
   lcd_goto(0,2);
   lcd_data("HEN GIO:");
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
   phutcu=ds1307.minute;
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while(true)
   {
      kt_nutnhan();
      chuyen_bcd_sang_dec();
      if(gio==giocai&&phut==phutcai&&giay==giaycai)
      {
         led32.ledx1[31]=1;
         led32_display();
      }
      if(buzzer_on_time>=30)
      {
         led32.ledx1[31]=0;
         led32_display();
         buzzer_on_time=buzzer_on_time-30;
      }
      if(bdn<10&&(ds1307.minute!=phutcu)) 
      {
         led32.ledx1[0]=1;
         led32_display();
      }
      else
      {
         phutcu=ds1307.minute;
         led32.ledx1[0]=0;
         led32_display();
      }
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
            lcd_goto(8,2);
            printf(lcd_data,"%u%u:%u%u:%u%u",
                              giocai/10%10, giocai%10,
                              phutcai/10%10, phutcai%10,
                              giaycai/10%10, giaycai%10);
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
   buzzer_on_time++;
}
