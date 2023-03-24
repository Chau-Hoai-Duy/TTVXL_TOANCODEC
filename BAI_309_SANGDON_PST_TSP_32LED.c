#define   BOARD     D501
#include<tv_boards.c>  
unsigned int8 i,j;
unsigned int32 Y,K;
void main()
{
      system_init();  
      while(true)
      {  Y=0X00000000;
         for(i=0;i<32;i++)
         {
            K=0X00000001;
            for(j=31;j>i;j--)
            {
               K=K<<1;
               led32.ledx32=Y|K;
               led32_display();
               delay_ms(50);
            }
            Y=Y|K;
         }
         Y=0X00000000;
         for(i=0;i<32;i++)
         {
            K=0X80000000;
            for(j=31;j>i;j--)
            {
               K=K>>1;
               led32.ledx32=Y|K;
               led32_display();
               delay_ms(50);
            }
            Y=Y|K;
         }
      }
}
