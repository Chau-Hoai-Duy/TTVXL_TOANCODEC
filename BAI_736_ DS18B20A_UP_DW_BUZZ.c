#define board D501
#include<tv_boards.c>
#include<tv_ds18b20.c>
unsigned int16 ng;
unsigned int8 gtcai=35;
void main()
{
   system_init();
   ds18b20_set_resolution(9); delay_us(20);
   while(true)
   {
      /*************************************cai nhiet do*********************************/
      if(inputcd(up)==0)
      {
         gtcai++;
         if(gtcai>=61) gtcai=60;
         d7seg_display();
      }
      if(inputcd(dw)==0)
      {
         gtcai--;
         if(gtcai<35) gtcai=35;
         d7seg_display();
      }
      /*************************************do nhiet do****************************************/
      if(ds18b20_read_temperature()==ok)
      {
         ng=ds18b20.temperatureA>>4;
         d7seg.led[1]=m7d[ng/10%10];
         d7seg.led[0]=m7d[ng%10];
         d7seg_display();
         if(ng<gtcai) 
         {
            triac_2_on();
            led32.ledx1[0]=0;
            led32_display();
         }
         else if(ng>gtcai) 
         {
            led32.ledx1[0]=1;
            led32_display();
            triac_2_off();
         }
      }
      d7seg.led[3]=m7d[gtcai/10%10];
      d7seg.led[2]=m7d[gtcai%10]-128;
   }
}
