/************************************ Yeu cau ****************************************************************
 1. Ban dau he thong dem san pham tu 10 den 20
 2. Moi lan nhan nut INV se reset ket qua dem va dao chieu dem san pham
 3. Nhan nut OFF de dung dem san pham
 4. Nhan nut ON de cho phep dem san pham lai
 
********************************* Cac lenh lien quan *********************************************************
 1. Lenh cau hinh che do hoat dong cho timer0 (vi phan cung da ket noi mach thu phat hong ngoai voi T0):
               ----------------------------------------------
                              setup_timer_0(mode);
               ----------------------------------------------
     . mode : T0_EXT_H_TO_L  => chon che do counter (dem xung ngoai tich cuc bang canh xuong)
     . mode : T0_EXT_L_TO_H  => chon che do counter (dem xung ngoai tich cuc bang canh lenh)
     . mode : T0_INTERNAL    => chon che do timer   
     . mode : T0_OFF         => dung T0 ( de dung T0 ta viet lenh : setup_timer_0(T0_OFF);)
                             => de cho T0 dem lai ta viet lenh setup_timer_0 ma khong co lua chon T0_OFF ben trong
     . mode : T0_8_BIT       => khong co lua chon nay thi T0 la 16 bit neu co them lua chon nay thi T0 la 8bit 
     . mode : T0_DIV_X       => chon bo chia truoc cho T0
     . Ta co the chon nhieu lua chon ben tren va giua cac lua chon cach nhau bang lenh OR ( | ) 
 2.Lenh dat truoc so dem:
                ----------------------------------------------
                                set_timer0(gt);
                ----------------------------------------------
     . Mac dinh T0 se dem tu 0 tro di tuy nhien ta co the cai dat truoc gia tri dem bat dau thong qua lenh 
       tren, sau khi thuc thi xong lenh tren T0 se dem tu "gt" tro len
     . Chu y: tranh nham lan lenh nay voi lenh "setup_timer_0"
 3.Lenh doc ket qua dem:
                ----------------------------------------------
                                 get_timer0();
                ---------------------------------------------- 
     . Lenh nay phai duoc thuc thi lien tuc de cap nhat gia tri dem moi, nen phai dat trong while (true)
               
*********************************** Chuong trinh *************************************************************/
#define   BOARD     D501
#include<tv_boards.c> 
unsigned int8 T0;
int1 mode=0;
void main()
{
      system_init(); 
      d7seg.led[2]= 0xbf;
      setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1);    // chon che do counter, bo chia truoc la 1
      set_timer0(10);                           // dem tu 10 tro len
      while(true)
      {     
           T0= get_timer0();                    // doc ket qua dem san pham
           if(mode) T0=(20+10)-T0;              // Neu che do dem xuong thi ta lay tong 2 gioi han tru gia tri dem
           if((T0>=21)||(T0<=9))set_timer0(11); // Khong che gioi han dem
           if(inputcd(INV)==0)                  // 2. Khi nhan nut INV se chuyen che do dem len - xuong, dong thoi reset gtri dem
            {
               mode=!mode; 
               set_timer0(10);
            }
           if(input(OFF)==0)  setup_timer_0(T0_OFF);                 //3. Khi nhan nut OFF thi dung dem san pham
           if(input(ON)==0)  setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1); // 4. Khi nhan nut ON thi cho phep dem san pham
           
           d7seg.led[1]= m7d[T0/10%10];
           d7seg.led[0]= m7d[T0/1%10];
           if(mode==0) d7seg.led[3]=0xff-8-16-32;     // Hien thi chu L tuong trung cho dem len
           else        d7seg.led[3]=0xff-2-4-16-32-64;// Hien thi chu X tuong trung cho dem xuong
           d7seg_display();   
      }
}
