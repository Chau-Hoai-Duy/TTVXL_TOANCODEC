#include<tv_boards.c>
#include<tv_key4x4.c>
signed int8 i=0, gtcaibd=0, dem=0, gtcaisau=0, j=0, jcu=0;
unsigned int16 k;
unsigned int1 cdo=0;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if((key4x4.key<=9)&&(key4x4.key!=13))
      {
         if(i==0)
         {
            gtcaibd=key4x4.key*10;
            d7seg.led[3]=m7d[key4x4.key];
         }
         if(i==1)
         {
            gtcaibd=gtcaibd+key4x4.key;
            d7seg.led[2]=m7d[key4x4.key];
            dem=0;
            gtcaisau=gtcaibd;
         }
         i++;
         if(i>=2) i=0;
      }
      else if(key4x4.key==13) cdo=~cdo;
      else;
   }
   d7seg_display();
}
void main()
{
   system_init();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
   d7seg.led[0]=m7d[0];
   d7seg.led[1]=m7d[0];
   d7seg.led[2]=m7d[0];
   d7seg.led[3]=m7d[0];
   while(true)
   {
      kt_nutnhan();
      j=get_timer0();
      if(j>100) 
      {
         set_timer0(0);
         j=get_timer0();
      }
      if(cdo==0)
      {
         if(j!=jcu)
         {
            jcu=j;
            dem++;
            if(dem>gtcaisau) dem=1;
         }
      }
      else
      {
         if(j!=jcu)
         {
            jcu=j;
            dem--;
            if(dem<0) dem=gtcaisau;
         }
      }
      if(i!=1)
      {
         for(k=0;k<=1;k++)
         {
            d7seg.led[2]=m7d[gtcaibd%10];
            delay_ms(1); kt_nutnhan();
            d7seg_display();
            d7seg.led[2]=0xff-128;
            delay_ms(1); kt_nutnhan();
            d7seg_display();
         }
      }
      d7seg.led[0]=m7d[dem%10];
      d7seg.led[1]=m7d[dem/10%10];
      d7seg.led[3]=m7d[gtcaibd/10%10];
   }
}

