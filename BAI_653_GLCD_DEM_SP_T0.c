#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
unsigned int8 dem=0;
void main()
{
   system_init();
   glcd_setup();
   setup_timer_0(T0_EXT_L_TO_H| T0_DIV_1);
   while(true)
   {
      dem=get_timer0();
      if(dem>=25) set_timer0(1);
      glcd_text_setup(50,20,3,1,1);
      printf(glcd_text,"%02d",dem);
      glcd_update();
   }
}
