#DEFINE BOARD D501
#include <tv_boards.c>
#include <tv_key4x4.c>
unsigned int8 cd=1;
unsigned int8 i;
unsigned int16 j,k;
void kiemtra_xuli_nutnhan()
{
   if(key4x4_read()==ok)
   {
     cd=key4x4.key;
     led32.ledx32=0;
     i=0;
     j=0;
     if(cd==0) cd=1;
   }
}
void chop_tat_led()
{
   led32.ledx32=~led32.ledx32;
   led32_display();
   delay_ms(500);
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
   while(true)
   {
      if(cd==1) chop_tat_led();
      if(cd==2) sang_tat_dan_pst();
      if(cd==3) sang_tat_dan_tsp();
      if(cd==4) sang_tat_dan_ngoai_vao();
      if(cd==5) sang_tat_dan_trong_ra();
      if(cd==6) sang_don_pst();
      if(cd==7) sang_don_tsp();
      else;
   }
}

