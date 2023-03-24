#DEFINE BOARD D501
#include<tv_boards.c>
void main()
{
system_init();
d7seg.led[3] = m7d[3];
d7seg.led[2] = m7d[2];
d7seg.led[1] = m7d[1];
d7seg.led[0] = m7d[0];
d7seg_display();
while(true)
   { 
   }    
}
