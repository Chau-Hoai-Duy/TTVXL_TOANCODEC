#define   BOARD     D501 
#include<tv_boards.c>
void kiemtra_xuli_nutnhan()
{
   if(inputcd(UP)==0)
   {
      led32.ledx16[0]=(led32.ledx16[0]<<1)|1;
   }
   else if(inputcd(DW)==0)
   {
      led32.ledx16[0]=(led32.ledx16[0])>>1;
   }
   else if(inputcd(CLR)==0)
   {
      led32.ledx16[0]=0;
   }
   led32_display();
}
void main()
{
      system_init();  
      while(true)
      {     
         kiemtra_xuli_nutnhan();
      }
}
  

