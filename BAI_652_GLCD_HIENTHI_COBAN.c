#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
unsigned int8 dem=0;
void main()
{
   system_init();
   glcd_setup();
   glcd_spkt_logo_raw(0);
   glcd_update();
   glcd_circle(70,7,6,1,1);
   glcd_update();
   glcd_rect(85,1,97,13,1,1);
   glcd_update();
   glcd_triangle(103,13,110,1,117,13,1,1);
   glcd_update();
   glcd_line(64,15,118,15,1);
   glcd_update();
   glcd_text_setup(80,56,1,1,1);
   glcd_text("SPKT");
   glcd_update();
   while(true)
   {
      glcd_text_setup(70,20,4,1,1);
      printf(glcd_text,"%02d",dem);
      glcd_update();
      dem++;
      dem%=100;
      delay_ms(500);
   }
}
