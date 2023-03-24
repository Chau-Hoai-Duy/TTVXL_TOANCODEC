#define   BOARD     D501
#include<tv_boards.c>  
UNSIGNED INT8 i,hu;
void sang_dan_pst()
{
   if(i<=32)
   {
      led32.ledx32=~(0xffffffff<<i);
      led32_display();
      delay_ms(100);
      i++;
   }
   else
   {
      i=0;
      hu=hu+1;
   }
}
void tat_dan_pst()
{
   if(i<=32)
   {
      led32.ledx32=0xffffffff<<i;
      led32_display();
      delay_ms(100);
      i++;
   }
   else
   {
      i=0;
      hu=hu+1;
   }
}
void main()
{
      system_init();
      i=0;
      hu=0;
      while(true)
      {
         if(hu==0) sang_dan_pst();
         else if(hu==1) tat_dan_pst();
         else if(hu==2) hu=0;
      }
}
