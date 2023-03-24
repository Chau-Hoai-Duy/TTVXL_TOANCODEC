#DEFINE BOARD D501
#include<tv_boards.c>
signed int8 gio=0, phut=0, giay=0, bdn=0, cdo=0,i;
void kt_nutnhan()
{
   if(inputcd(mod)==0)
   {
      cdo++;
      if(cdo>=4) cdo=0;
   }
   if(inputcd(up)==0)
   {
      if(cdo==1) 
      {
         giay++;
         if(giay>=60) giay=0;
      }
      else if(cdo==2) 
      {
         phut++;
         if(phut>=60) phut=0;
      }
      else if(cdo==3) 
      {
         gio++;
         if(gio>=13) gio=1;
      }
   }
   if(inputcd(dw)==0)
   {
      if(cdo==1) 
      {
         giay--;
         if(giay<0) giay=59;
      }
      else if(cdo==2) 
      {
         phut--;
         if(phut<0) phut=59;
      }
      else if(cdo==3) 
      {
         gio--;
         if(gio<=0) gio=12;
      }
   }
}
void main()
{
   system_init();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while(true)
   {
      kt_nutnhan();
      if(bdn>=10)
      {
         bdn=bdn-10;
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
      }
      s7seg.led[0]=m7d[giay%10];
      s7seg.led[1]=m7d[giay/10%10];
      s7seg.led[2]=0xff-64;
      s7seg.led[3]=m7d[phut%10];
      s7seg.led[4]=m7d[phut/10%10];
      s7seg.led[5]=0xff-64;
      s7seg.led[6]=m7d[gio%10];
      s7seg.led[7]=m7d[gio/10%10];
      if(cdo==1) s7seg.led[0]=m7d[giay%10]-128;
      if(cdo==2) s7seg.led[3]=m7d[phut%10]-128;
      if(cdo==3) s7seg.led[6]=m7d[gio%10]-128;
      s7seg_display();
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
