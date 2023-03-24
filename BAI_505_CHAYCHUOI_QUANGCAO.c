//#DEFINE BOARD D501
#include<tv_boards.c>
//                           H                  E               L            L           O      _                 C               H          O    _      1      _      L             Y            _        C               A                F                    E
unsigned int8 CHUOI[]={0xff-2-4-16-32-64,0XFF-1-32-64-16-8,0xff-8-16-32,0xff-8-16-32,0xC0-128,0xff,0xff-1-32-16-8,0xff-2-4-16-32-64,0xc0,0xff,0xff-2-4,0xff,0xff-8-16-32,0xff-2-4-32-64,0xff,0xff-1-32-16-8,0xff-1-2-4-16-32-64,0xff-1-32-64-16,0XFF-1-32-64-16-8,0xff};
unsigned int8 i,n;
void main()
{
   system_init();
   i=0;
   while(true)
   {
            s7seg.led[7]=s7seg.led[6];
            s7seg.led[6]=s7seg.led[5];
            s7seg.led[5]=s7seg.led[4];
            s7seg.led[4]=s7seg.led[3];
            s7seg.led[3]=s7seg.led[2];
            s7seg.led[2]=s7seg.led[1];
            s7seg.led[1]=s7seg.led[0];
            if(i<=19)
            {
               s7seg.led[0]=chuoi[i];
               for(n=0;n<100;n++) 
               {
                  s7seg_display();
               }
               i++;
            }
            else i=0;
   }
}
