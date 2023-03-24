#DEFINE BOARD D501
#include<tv_boards.c>
void main()
{
   system_init();
   led32.ledx8[0]=0x00;
   while(true)
   {
     if(input(ON)==0) led32.ledx8[0]=0xff;
     else if(input(OFF)==0) led32.ledx8[0]=0x00;
     led32_display();
   }
}
