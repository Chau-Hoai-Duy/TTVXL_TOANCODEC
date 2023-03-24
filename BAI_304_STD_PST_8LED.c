#define   BOARD     D501
#include<tv_boards.c>  
unsigned int8 i,Y;
void main()
{
      system_init();  
      while(true)
      {  Y=0X00;
         for(i=0;i<8;i++)
         {
            Y=Y<<1|0X01;
            led32.ledx8[0]=Y;
            led32_display();
            delay_ms(1000);
         }
         for(i=0;i<8;i++)
         {
            Y=Y<<1;
            led32.ledx8[0]=Y;
            led32_display();
            delay_ms(1000);
         }
      }
}
