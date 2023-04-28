//#DEFINE BOARD D501
#include <tv_boards.c>
#include <tv_key4x4.c>
void kt_keypad()
{
   if(key4x4_read()==ok)
   {
      if(key4x4.key<8)
      {
         led32.ledx32=((int32)1<<key4x4.key)|led32.ledx32;
      }
      else
      {
         led32.ledx32=(~((int32)1<<(key4x4.key-8)))&led32.ledx32;
      }
   }
}
void main()
{
   system_init();
   while(true)
   {
      kt_keypad();
      led32_display();
   }
}

