#define   BOARD     D501
#include<tv_boards.c>  
unsigned int8 i;
unsigned int16 Y;
void main()
{
      system_init();  
      while(true)
      {  Y=0X0000;
         for(i=0;i<16;i++)
         {
            Y=Y>>1|0X8000;
            led32.ledx16[0]=Y;
            led32.ledx16[1]=Y;
            led32_display();
            delay_ms(1000);
         }
         for(i=0;i<16;i++)
         {
            Y=Y>>1;
            led32.ledx16[0]=Y;
            led32.ledx16[1]=Y;
            led32_display();
            delay_ms(1000);
         }
      }
}
