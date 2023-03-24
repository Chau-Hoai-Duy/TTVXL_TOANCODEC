//#define   BOARD     D501 
#include<tv_boards.c>
#include<tv_key4x4.c>
unsigned int8 cd=1,cdold=1;
unsigned int8 i,T0=0, T0old=0;
unsigned int16 j,k;
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
      if(inputcd(up)==0)
      {
        led32.ledx32=0;
        i=0;
        j=0;
        if(cd==7) cd=7;
        else cd++;
      }
      if(inputcd(dw)==0) 
      {
         led32.ledx32=0;
         i=0;
         j=0;
         if(cd==1) cd=1;
         else cd--;
      }
      if(inputcd(clr)==0) 
      {
         i=0;
         cd=1;
      }
}
void chop_tat_led()
{
   led32.ledx32=~led32.ledx32;
   led32_display();
   for(j=0;j<=2000;j++)   kiemtra_xuli_nutnhan();
}
void sang_tat_dan_pst()
{
   if(i<=64)
   {
      if(i<32)  led32.ledx32=(led32.ledx32<<1)|1;
      if(i>=32) led32.ledx32=led32.ledx32<<1;
      led32_display();
      delay_ms(50);
      i++;
      kiemtra_xuli_nutnhan();
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
         delay_ms(50);
         i++;
         kiemtra_xuli_nutnhan();
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
      delay_ms(50);
      kiemtra_xuli_nutnhan();
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
      delay_ms(50);
      kiemtra_xuli_nutnhan();
      i++;
   }
   else i=0;
}
void sang_don_pst()
{
   if(i<=32)
   {
      if(j<32-i)
      {
         led32.ledx32=~(0xffffffff>>i)|((int32)1<<j);
         j++;
         delay_ms(50);
         led32_display();
         kiemtra_xuli_nutnhan();
      }
      else 
      {
         j=0;
         i++;  
      }
   }
   else i=0;
}
void sang_don_tsp()
{
   if(i<=32)
   {
      if(j<32-i)
      {
         led32.ledx32=~(0xffffffff<<i)|(0x80000000>>j);
         j++;
         delay_ms(50);
         led32_display();
         kiemtra_xuli_nutnhan();
      }
      else 
      {
         j=0;
         i++;
      }
   }
   else i=0;
}
void main()
{
      system_init();
      setup_timer_0(t0_ext_l_to_h|t0_div_1);
      set_timer0(98);
      while(true)
      {  
         T0=get_timer0();
         if(T0>100) set_timer0(1);
         if(T0!=T0old)
         {
            T0old=T0;
            d7seg_xoa0VN(T0);
         }
         if(cd==1) chop_tat_led();
         if(cd==2) sang_tat_dan_pst();
         if(cd==3) sang_tat_dan_tsp();
         if(cd==4) sang_tat_dan_ngoai_vao();
         if(cd==5) sang_tat_dan_trong_ra();
         if(cd==6) sang_don_pst();
         if(cd==7) sang_don_tsp();
         
      }
}
