#define   BOARD     D501 
#include<tv_boards.c>
unsigned int1 cd=0;
void kiemtra_xuli_nutnhan()
{
   if(inputcd(CLR)==0)
      {
         cd=~cd;
         led32.ledx16[0]=0;
      }
   if(cd==0)
   {
      if(inputcd(UP)==0)
      {
         led32.ledx16[0]=(led32.ledx16[0]<<1)|1;
      }
      else if(inputcd(DW)==0)
      {
         led32.ledx16[0]=(led32.ledx16[0])>>1;
      }
   }
   if(cd==1)
   {
      if(inputcd(UP)==0)
      {
         led32.ledx16[0]=(led32.ledx16[0]>>1)|0x8000;
      }
      else if(inputcd(DW)==0)
      {
         led32.ledx16[0]=(led32.ledx16[0])<<1;
      }
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
  

