#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_glcd.c>
unsigned int8 mode=2,bdn=0,giay=0,sp;
void ve_giaodien()
{
   //xoa toan bo man hinh
   glcd_clear(0);
   //ve thanh chonj lua
   glcd_rect(0,mode*20, 50, mode*20+20, 1,1);
   //ve noi dung cua menu
   glcd_text_setup(5,7,1,mode!=0,0); 
   glcd_text("COUNTER"); 
   glcd_text_setup(5,27,1,mode!=1,0); 
   glcd_text("TIMER"); 
   glcd_text_setup(5,47,1,mode!=2,0); 
   glcd_text("LOGO");
   //neu mode bang 2 thi hien thi logo 
   if(mode==2) glcd_spkt_logo_raw(64);
   // neu mode bang 0 hoac bang 1 thi hien thi hinh tron
   else 
   { //ve duong tron day 3 pixel
      glcd_circle(95,31,20,1,1); 
      glcd_circle(95,31,17,1,0);
   }
   //hien thi ra man hinh
   glcd_update();
}
void main()
{
   system_init();
   glcd_setup();
   ve_giaodien(); 
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   while(true)
   { // Moi lan nhan nut moi ve lai giao dien mot lan de tranh tri hoan cac tac vu khac
      if((inputcd(DW)==0)&&(mode<2)) {mode++; ve_giaodien();}
      if((inputcd(UP)==0)&&(mode>0)) {mode--; ve_giaodien();}
      sp = get_timer0();
      if(sp>24) set_timer0(1);
      if(bdn>=10)
      {
         bdn=bdn-10; giay++;
         giay%=60;
      }
      glcd_text_setup(85,24,2,1,1);
      if(mode==0) printf(glcd_text,"%02u",sp);
      else if(mode==1) printf(glcd_text,"%02u",giay);
      glcd_update();
   } 
}
#INT_TIMER1
void ngatT1()
{
   set_timer1(3036);
   bdn++; 
}
