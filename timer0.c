#define led1 pin_d1
#include <18F4550.h>
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 //Configuração dos fusíveis
#use delay(clock=8000000)
#int_timer0
void funcao_tempo(){
   static boolean flag;
   static unsigned int32 n;
   set_timer0(240+get_timer0());
   n++;
   if (n==30){
      n=0;
      flag=!flag;
      output_bit(led1,flag);
   }
}
void main() {
                  //prescaler
   setup_timer_0 (RTCC_DIV_2|RTCC_INTERNAL | RTCC_8_BIT );
   set_timer0(240);
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER0);
   while(true) {}
}
