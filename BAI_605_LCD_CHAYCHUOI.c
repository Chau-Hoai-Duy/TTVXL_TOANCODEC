#DEFINE BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>
unsigned char S[]="TRUONG DAI HOC SU PHAM KY THUAT TP.HCM";
unsigned char RONG[]="                    ";
signed int8 giay=0;
signed int8 chieu=1;
unsigned int8 i=0,j=0,k=0;
void hienthi_muiten()
{
   if(chieu==1)
   {
      lcd_goto(0,1);
      lcd_data(0x7e);
      lcd_goto(0,2);
      lcd_data(" ");
   }
   else
   {
      lcd_goto(0,1);
      lcd_data(" ");
      lcd_goto(0,2);
      lcd_data(0x7e);
   }
}
void kt_nutnhan()
{
   if(inputcd(inv)==0)
   {
      chieu=-chieu;
      hienthi_muiten();
      break;
   }
}
void main()
{
   system_init();
   lcd_setup();
   lcd_goto(1,1);
   lcd_data("DEM LEN");
   lcd_goto(1,2);
   lcd_data("DEM XUONG");
   hienthi_muiten();
   while(true)
   { 
       
        for(j=0;j<19;j++)
        {
            RONG[j]=RONG[j+1];
        }
        if(k<38)
        {
            RONG[19]=S[k];
            k++;
        }
        else 
        {
            k=0;
            RONG[19]=0X20;
        }
        lcd_goto(0,0);
        for(i=0;i<19;i++) 
        {
            lcd_data(RONG[i]);
        }
        for(j=0;j<250;j++) kt_nutnhan();
        lcd_goto(9,3);
        printf(lcd_data,"%02u",giay);
        giay=giay+chieu;
        if(giay>=60) giay=0;
        else if(giay<0) giay=59;
        for(j=0;j<100;j++)
         {
            kt_nutnhan();
            delay_ms(10);
         }
   }
}
//!#include<tv_boards.c>
//!#include<tv_lcd.c>
//!const unsigned int8 chuoi[]="                    DAI HOC SU PHAM KY THUAT THANH PHO HO CHI MINH                    ";
//!void main() 
//!{
//!      system_init();  
//!      lcd_setup();  
//!      while(true)
//!      {    
//!            for(int8 n=0;n<sizeof(chuoi)-20;n++)
//!            {
//!               lcd_goto(0,0);
//!               for(int8 m=n;m<n+20;m++)lcd_data(chuoi[m]);     
//!               delay_ms(200);
//!            }     
//!      }
//!}
