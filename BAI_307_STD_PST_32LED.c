#define   BOARD     D501
#include<tv_boards.c>  
unsigned int8 i;
unsigned int32 Y;
void main()
{
      system_init();  
      while(true)
      {  Y=0X00000000;
         for(i=0;i<32;i++)
         {
            Y=Y>>1|0X80000000;
            led32.ledx32=Y;
            led32_display();
            delay_ms(300);
         }
         for(i=0;i<32;i++)
         {
            Y=Y>>1;
            led32.ledx32=Y;
            led32_display();
            delay_ms(300);
         }
      }
}
