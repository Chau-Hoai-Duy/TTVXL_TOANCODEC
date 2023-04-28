#INCLUDE <TV_BOARDS.c>

#DEFINE ND_TREN  40

UNSIGNED INT8     J, SOLAN=100;

UNSIGNED INT16   LM35A;

INT1 TTQN=0;

VOID SO_SANH_DK_BUZZER()

{

      IF ((LM35A>ND_TREN)&&(TTQN==0))

{

         TTQN =1;

         BUZZER_ON();

}

      ELSE IF ((LM35A<ND_TREN)&&(TTQN==1))

{

         TTQN =0;

         BUZZER_OFF();

}

}

VOID MAIN()

{

   SYSTEM_INIT();

   SETUP_ADC(ADC_CLOCK_DIV_32);

   SETUP_ADC_PORTS(AN0|VSS_VDD );

   SET_ADC_CHANNEL(0);

   TTQN =0;

   WHILE(TRUE)

{

      LM35A =0;

      FOR (J=0; J<SOLAN; J++)

{

         LM35A = LM35A + READ_ADC();

         DELAY_MS(1);

}

      LM35A = LM35A /2.046;

      LM35A = LM35A /SOLAN;

      SO_SANH_DK_BUZZER();

}

}
