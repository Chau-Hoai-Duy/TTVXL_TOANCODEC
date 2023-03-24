#include<tv_boards.c>
#include<tv_key4x4.c>
signed int8 i=0, gtcaibd=0, dem=0, gtcaisau=0, j=0, jcu=0, bdn;
unsigned int8 gio, phut, giay, k, caitg, cdoidt;
unsigned int1 cdoi=0, cdocount=0;
void kt_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key<=9)
      {
         if(i==0)
         {
            gtcaibd=key4x4.key*10;
            caitg=key4x4.key*10;
         }
         if(i==1)
         {
            gtcaibd=gtcaibd+key4x4.key;
            caitg=caitg+key4x4.key;
            gtcaisau=gtcaibd;
         }
         i++;
         if(i>=2) i=0;
      }
      else if(key4x4.key==13) cdocount=~cdocount;
      else if(key4x4.key==12) cdoi=~cdoi;
      else if(key4x4.key==14)
      {
         cdoidt++;
         caitg=0;
         if(cdoidt>=4) cdoidt=0;
      }
   }
}
void main()
{
   system_init();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   set_timer0(0);
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
/******************************XU LY DEM SAN PHAM***********************************************/
      if(cdoi==0)
      {
         j=get_timer0();
         if(j>100) 
         {
            set_timer0(0);
            j=get_timer0();
         }
         if(cdocount==0)
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
         if(i==1)
         {
            if(k<50)
            {
               s7seg.led[4]=0xff;
               s7seg_display();
               k++;
            }
            else if((k>=50)&&(k<100))
            {
               s7seg.led[4]=m7d[gtcaisau%10]-128;
               s7seg_display();
               k++;
            }
            else k=0;
         }
         else s7seg.led[4]=m7d[gtcaisau%10]-128;
         s7seg.led[0]=0xff;
         s7seg.led[1]=0xff;
         s7seg.led[2]=m7d[dem%10];
         s7seg.led[3]=m7d[dem/10%10];
         s7seg.led[5]=m7d[gtcaibd/10%10];
         s7seg.led[6]=0xff;
         s7seg.led[7]=0xff;
         s7seg_display();
     }
/******************************DEM GIAY CHINH XAC DUNG TIMER 1***************************************/
      if(cdoi==1)
      {
         s7seg.led[0]=m7d[giay%10];
         s7seg.led[1]=m7d[giay/10%10];
         s7seg.led[2]=0xff-64;
         s7seg.led[3]=m7d[phut%10];
         s7seg.led[4]=m7d[phut/10%10];
         s7seg.led[5]=0xff-64;
         s7seg.led[6]=m7d[gio%10];
         s7seg.led[7]=m7d[gio/10%10];
         if(cdoidt==1)
         {
            gio=caitg;
            if(gio>=13)
            {
               gio=0;
               i=0;
            }
            s7seg.led[6]=0xff;
            s7seg.led[7]=0xff;
            if(k<30)
            {
               s7seg_display();
               kt_nutnhan();
               k++;
            }
            else if((k>=30)&&(k<60))
            {
               s7seg.led[6]=m7d[gio%10];
               s7seg.led[7]=m7d[gio/10%10];
               s7seg_display();
               k++;
            }
            else k=0;
         }
         if(cdoidt==2)
         {
            phut=caitg;
            if(phut>=60)
            {
               phut=0;
               i=0;
            }
            s7seg.led[3]=0xff;
            s7seg.led[4]=0xff;
            if(k<30)
            {
               s7seg_display();
               kt_nutnhan();
               k++;
            }
            else if((k>=30)&&(k<60))
            {
               s7seg.led[3]=m7d[phut%10];
               s7seg.led[4]=m7d[phut/10%10];
               s7seg_display();
               k++;
            }
            else k=0;
         }
         if(cdoidt==3)
         {
            giay=caitg;
            if(giay>=60)
            {
               giay=0;
               i=0;
            }
            s7seg.led[0]=0xff;
            s7seg.led[1]=0xff;
            if(k<30)
            {
               s7seg_display();
               kt_nutnhan();
               k++;
            }
            else if((k>=30)&&(k<60))
            {
               s7seg.led[0]=m7d[giay%10];
               s7seg.led[1]=m7d[giay/10%10];
               s7seg_display();
               kt_nutnhan();
               k++;
            }
            else k=0;
         }
         else s7seg_display();
      }  
   }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}

