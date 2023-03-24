//#define   BOARD     D501 
#include<tv_boards.c>
#include<tv_key4x4.c>
unsigned int8 cd=1,cdold=1;
unsigned int8 i,T0=0, T0old=0;
unsigned int16 j,k;
unsigned int8 gio=0, phut=0, giay=0, bdn=0, cdo=0,m,l;
void d7seg_xoa0VN(unsigned int16 d)
{
   unsigned int8 n=0;
   do
   {  d7seg.led[n]= m7d[d%10];
      d/=10;n++;
   }while(d!=0);
   for(;n<4;n++) d7seg.led[n]= 0xff;
   d7seg_display();
}
void kiemtra_xuli_nutnhan()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key==1)
      {
        led32.ledx32=0;
        i=0;
        j=0;
        if(cd==5) cd=5;
        else cd++;
      }
      if(key4x4.key==2) 
      {
         led32.ledx32=0;
         i=0;
         j=0;
         if(cd==1) cd=1;
         else cd--;
      }
   }
      if(inputcd(clr)==0) 
      {
         i=0;
         cd=1;
      }
      if(inputcd(mod)==0)
      {
         cdo++;
         if(cdo>=4) cdo=0;
      }
      if(inputcd(up)==0)
      {
         if(cdo==1) giay++;
         else if(cdo==2) phut++;
         else if(cdo==3) gio++;   
      }
      if(inputcd(dw)==0)
      {  
         if(cdo==1) giay--;
         else if(cdo==2) phut--;
         else if(cdo==3) gio--;
      }
}
/*********************************DIEU KHIEN 32 LED*****************************/
void chop_tat_led()
{
   led32.ledx32=~led32.ledx32;
   led32_display();
   for(j=0;j<=20;j++) 
   {
      kiemtra_xuli_nutnhan();
      s7seg_display();
   }
}
void sang_tat_dan_pst()
{
   if(i<=64)
   {
      if(i<32)  led32.ledx32=(led32.ledx32<<1)|1;
      if(i>=32) led32.ledx32=led32.ledx32<<1;
      led32_display();
      s7seg_display();
      i++;
      for(l=0;l<=20;l++) 
      {
         kiemtra_xuli_nutnhan();
         s7seg_display();
      }
   }
   else
      i=0;
}
void sang_tat_dan_tsp()
{
   if(i<=64)
      {
         if(i<32)  led32.ledx32=(led32.ledx32>>1)|0x80000000;
         if(i>=32) led32.ledx32=led32.ledx32>>1;
         led32_display();
         s7seg_display();
         i++;
         for(l=0;l<=20;l++)
         {
            kiemtra_xuli_nutnhan();
            s7seg_display();
         }
      }
      else
         i=0;
}
void sang_tat_dan_ngoai_vao()
{
   if(i<=32)
   {
      if(i<16) 
      {
         led32.ledx16[1]=(led32.ledx16[1]>>1)|0x8000;
         led32.ledx16[0]=(led32.ledx16[0]<<1)|0x0001;
      }
      if(i>=16) 
      {
         led32.ledx16[1]=(led32.ledx16[1]>>1);
         led32.ledx16[0]=(led32.ledx16[0]<<1);
      }
      led32_display();
      s7seg_display();
      for(l=0;l<=20;l++) 
      {
         kiemtra_xuli_nutnhan();
         s7seg_display();
      }
      i++;
   }
   else i=0;
}
void sang_tat_dan_trong_ra()
{
   if(i<=32)
   {
      if(i<16) 
      {
         led32.ledx16[1]=(led32.ledx16[1]<<1)|0x0001;
         led32.ledx16[0]=(led32.ledx16[0]>>1)|0x8000;
      }
      if(i>=16) 
      {
         led32.ledx16[1]=(led32.ledx16[1]<<1);
         led32.ledx16[0]=(led32.ledx16[0]>>1);
      }
      led32_display();
      s7seg_display();
      for(l=0;l<=20;l++) 
      {
         kiemtra_xuli_nutnhan();
         s7seg_display();
      }
      i++;
   }
   else i=0;
}
/***********************************HAM CHINH*************************************************/
void main()
{
      system_init();
      setup_timer_0(t0_ext_l_to_h|t0_div_1);
      set_timer0(98);
      setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
      set_timer1(3036);
      enable_interrupts(int_timer1);
      enable_interrupts(global);
      while(true)
      {  
         /****************************DEM SP HIEN THI 32 LED********************************/
         T0=get_timer0();
         if(T0>100) set_timer0(1);
         if(T0!=T0old)
         {
            T0old=T0;
            d7seg_xoa0VN(T0);
         }
         if(cd==1)
         {
            chop_tat_led();
            if(T0>100) set_timer0(1);
         }
         if(cd==2) 
         {
            sang_tat_dan_pst();
            if(T0>100) set_timer0(1);
         }
         if(cd==3) 
         {
            sang_tat_dan_tsp();
            if(T0>100) set_timer0(1);
         }
         if(cd==4) 
         {
            sang_tat_dan_ngoai_vao();
            if(T0>100) set_timer0(1);
         }
         if(cd==5) 
         {
            sang_tat_dan_trong_ra();
            if(T0>100) set_timer0(1);
         }
         /*******************************DEM GIO PHUT GIAY*********************************/
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
      if(cdo==1)
      {
         s7seg.led[0]=0xff;
         s7seg.led[1]=0xff;
         if(m<2)
         {
            s7seg_display();
            kiemtra_xuli_nutnhan();
            if(T0>100) set_timer0(1);
            m++;
         }
         else if(m<4)
         {
            s7seg.led[0]=m7d[giay%10];
            s7seg.led[1]=m7d[giay/10%10];
            s7seg_display();
            kiemtra_xuli_nutnhan();
            if(T0>100) set_timer0(1);
            m++;
         }
         else m=0;
      }
      else if(cdo==2)
      {
         s7seg.led[3]=0xff;
         s7seg.led[4]=0xff;
         if(m<2)
         {
            s7seg_display();
            kiemtra_xuli_nutnhan();
            if(T0>100) set_timer0(1);
            m++;
         }
         else if(m<4)
         {
            s7seg.led[3]=m7d[phut%10];
            s7seg.led[4]=m7d[phut/10%10];
            s7seg_display();
            kiemtra_xuli_nutnhan();
            if(T0>100) set_timer0(1);
            m++;
         }
         else m=0;
      }
      else if(cdo==3)
      {
         s7seg.led[6]=0xff;
         s7seg.led[7]=0xff;
         if(m<2)
         {
            s7seg_display();
            kiemtra_xuli_nutnhan();
            if(T0>100) set_timer0(1);
            m++;
         }
         else if(m<4)
         {
            s7seg.led[6]=m7d[gio%10];
            s7seg.led[7]=m7d[gio/10%10];
            s7seg_display();
            kiemtra_xuli_nutnhan();
            if(T0>100) set_timer0(1);
            m++;
         }
         else m=0;
      }
      else
      s7seg_display();
      if(T0>100) set_timer0(1);
      }
}
#int_timer1
void ngat_timer1()
{
   set_timer1(3036);
   bdn++;
}
