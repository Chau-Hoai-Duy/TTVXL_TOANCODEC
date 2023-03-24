#define   BOARD     D501
#include<tv_boards.c>  
UNSIGNED INT8 j,i,hu;
void chop_tat_5_lan()
{
   if(j<10)
   {
      led32.ledx32=~led32.ledx32;
      led32_display();
      delay_ms(500);
      j++;
   }
   else
   {
      j=0;
      hu++;
   }
}
void sang_dan_pst()
{
   if(i<=32)
   {
      led32.ledx32=~(0xffffffff<<i);
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void tat_dan_pst()
{
   if(i<=32)
   {
      led32.ledx32=0xffffffff<<i;
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void sang_dan_tsp()
{
   if(i<=32)
   {
      led32.ledx32=~(0xffffffff>>i);
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void tat_dan_tsp()
{
   if(i<=32)
   {
      led32.ledx32=0xffffffff>>i;
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void sang_dan_ngoai_vao()
{
   if(i<=16)
   {
      led32.ledx16[1]=~(0xffff>>i);
      led32.ledx16[0]=~(0xffff<<i);
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void tat_dan_ngoai_vao()
{
   if(i<=16)
   {
      led32.ledx16[1]=0xffff>>i;
      led32.ledx16[0]=0xffff<<i;
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void sang_dan_trong_ra()
{
   if(i<=16)
   {
      led32.ledx16[1]=~(0xffff<<i);
      led32.ledx16[0]=~(0xffff>>i);
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void tat_dan_trong_ra()
{
   if(i<=16)
   {
      led32.ledx16[1]=0xffff<<i;
      led32.ledx16[0]=0xffff>>i;
      led32_display();
      delay_ms(200);
      i++;
   }
   else
   {
      i=0;
      hu++;
   }
}
void main()
{
      system_init();
      j=0;
      i=0;
      hu=0;
      while(true)
      {
         if(hu==0) chop_tat_5_lan();
         else if(hu==1) sang_dan_pst();
         else if(hu==2) tat_dan_pst();
         else if(hu==3) sang_dan_pst();
         else if(hu==4) tat_dan_pst();
         else if(hu==5) chop_tat_5_lan();
         else if(hu==6) sang_dan_tsp();
         else if(hu==7) tat_dan_tsp();
         else if(hu==8) sang_dan_tsp();
         else if(hu==9) tat_dan_tsp();
         else if(hu==10) chop_tat_5_lan();
         else if(hu==11) sang_dan_ngoai_vao();
         else if(hu==12) tat_dan_ngoai_vao();
         else if(hu==13) sang_dan_ngoai_vao();
         else if(hu==14) tat_dan_ngoai_vao();
         else if(hu==15) chop_tat_5_lan();
         else if(hu==16) sang_dan_trong_ra();
         else if(hu==17) tat_dan_trong_ra();
         else if(hu==18) sang_dan_trong_ra();
         else if(hu==19) tat_dan_trong_ra();
         else if(hu==20) hu=0;
      }
}
