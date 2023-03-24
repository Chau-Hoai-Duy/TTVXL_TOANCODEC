#include<tv_boards.c>  
unsigned int8 i,j,cdo=1,cdocu=1, cho=1, chocu=1;
unsigned int1 cdoi=0;
unsigned int8 k;
void kt_nut_nhan()
{
   if(inputcd(mod)==0) cdoi=~cdoi;
   if(cdoi==0)
   {
      if(inputcd(up)==0) cdo++;
      if(inputcd(dw)==0) cdo--;
      led32.ledx1[0]=0;
      led32_display();
   }
   else
   {
      if(inputcd(up)==0) cho--;
      if(inputcd(dw)==0) cho++;
      led32.ledx1[0]=1;
      led32_display();
   }
   if(cdo<1) cdo=1;
   if(cdo>=10) cdo=10;
   if(cho<1) cho=1;
   if(cho>=10) cho=10;
   if(cdo!=cdocu)
   {
      i=0;
      j=4;
      led32.ledx32=0;
      cdocu=cdo;
      break;
   }
   if(cho!=chocu)
   {
      chocu=cho;
      break;
   }
   delay_ms(50);
}
void chop_tat_led_don()
{
   if(i<=2)
   {
      led32.ledx32=(~led32.ledx32)&0x0ffffff0;
      led32_display();
      for(k=0;k<=cho;k++) kt_nut_nhan();
      i++;
   }
   else i=0;
}
void sang_tat_dan_pst()
{
   if(i<48)
   {
      if(i<24) led32.ledx32=((led32.ledx32<<1)|0x00000010)&0x0ffffff0;
      else     led32.ledx32=(led32.ledx32<<1)&0x0ffffff0;
      led32_display();
      i++;
      for(k=0;k<=cho;k++) kt_nut_nhan();
   }
   else i=0;
}
void sang_tat_dan_tsp()
{
   if(i<48)
   {
      if(i<24) led32.ledx32=((led32.ledx32>>1)|0x08000000)&0x0ffffff0;
      else     led32.ledx32=(led32.ledx32>>1)&0x0ffffff0;
      led32_display();
      for(k=0;k<=cho;k++) kt_nut_nhan();
      i++;
   }
   else i=0;
}
void sang_dich_pst()
{
   if(i<24)
   {
      led32.ledx32=0x00000010<<i;
      led32_display();
      i++;
      for(k=0;k<=cho;k++) kt_nut_nhan();
   }
   else i=0;
}
void sang_dich_tsp()
{
   if(i<24)
   {
      led32.ledx32=0x08000000>>i;
      led32_display();
      i++;
      for(k=0;k<=cho;k++) kt_nut_nhan();
   }
   else i=0;
}
void sang_tat_dan_tu_trong_ra()
{
   if(i<24)
   {
      if(i<12) 
      {
         led32.ledx16[1]=(led32.ledx16[1]<<1)|0x0001;
         led32.ledx16[0]=(led32.ledx16[0]>>1)|0x8000;
      }
      else
      {
         led32.ledx16[1]=(led32.ledx16[1]<<1)&0x0fff;
         led32.ledx16[0]=(led32.ledx16[0]>>1)&0xfff0;
      }
      led32_display();
      i++;
      for(k=0;k<=cho;k++) kt_nut_nhan();
   }
   else i=0;
}
void sang_tat_dan_tu_ngoai_vao()
{
   if(i<24)
   {
      if(i<12)
      {
         led32.ledx16[1]=((led32.ledx16[1]>>1)|0x0800)&0x0fff;
         led32.ledx16[0]=((led32.ledx16[0]<<1)|0x0010)&0xfff0;
      }
      else
      {
         led32.ledx16[1]=(led32.ledx16[1]>>1)&0x0fff;
         led32.ledx16[0]=(led32.ledx16[0]<<1)&0xfff0;
      }
      led32_display();
      i++;
      for(k=0;k<=cho;k++) kt_nut_nhan();
   }
   else i=0;
}
void sang_dich_tu_trong_ra()
{
   if(i<12)
   {
      led32.ledx16[0]=0x8000>>i;
      led32.ledx16[1]=0x0001<<i;
      led32_display();
      i++;
      for(k=0;k<=cho;k++) kt_nut_nhan();
   }
   else i=0;
}
void sang_dich_tu_ngoai_vao()
{
   if(i<12)
   {
      led32.ledx16[0]=0x0010<<i;
      led32.ledx16[1]=0x0800>>i;
      led32_display();
      i++;
      for(k=0;k<=cho;k++) kt_nut_nhan();
   }
   else i=0;
}
void sang_don_pst()
{
   if(i<24)
   {
      if(j<28-i)
      {
         led32.ledx32=((~(0x0fffffff>>i))|((int32)1<<j))&0x0ffffff0;
         led32_display();
         for(k=0;k<=cho;k++) kt_nut_nhan();
         j++;
      }
      else
      {
         j=4;
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
         if(cdo==1) chop_tat_led_don();
         if(cdo==2) sang_tat_dan_pst();
         if(cdo==3) sang_tat_dan_tsp();
         if(cdo==4) sang_dich_pst();
         if(cdo==5) sang_dich_tsp();
         if(cdo==6) sang_tat_dan_tu_trong_ra();
         if(cdo==7) sang_tat_dan_tu_ngoai_vao();
         if(cdo==8) sang_dich_tu_ngoai_vao();
         if(cdo==9) sang_dich_tu_trong_ra();
         if(cdo==10) sang_don_pst();
      }
}

