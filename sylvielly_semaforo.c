/*PRATICA - TIMER0 - MICROCONTROLADORES*/
/*EQUIPE: KARINE MENDES / LINDALVA ALMEIDA / SYLVIELLY SOUSA*/

#include <18F4550.h>
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 //Configuração dos fusíveis
#use delay(clock=20000000)

#define VERMELHO pin_d1       //pino D1
#define AMARELO  pin_d2       //pino D2
#define VERDE    pin_d3       //pino D3

#define VERMELHO1 pin_c1      //pino C4
#define AMARELO1  pin_c2      //pino C5
#define VERDE1    pin_c4      //pino C6

#int_timer0
//PROGRAMA PARA PISCAR O LED A CADA 1s
void funcao_tempo()
{
//static boolean flag;                //variavel do tipo booleana
   static unsigned int32 n;            
   set_timer0(131+get_timer0());
   n++;
     
      if (n==1875)                     //ajuste de 'n' para 2s
      {
      //semaforo1   
         output_low(VERDE);
         output_high(AMARELO);
         output_low(VERMELHO);
      //semaforo2
         output_low(VERDE1);
         output_low(AMARELO1);
         output_high(VERMELHO1);
      }
      
      if (n==3125)                     //
      {
         //semaforo1
         output_low(VERDE);
         output_low(AMARELO);
         output_high(VERMELHO);
         //semaforo2
         output_high(VERDE1);
         output_low(AMARELO1);
         output_low(VERMELHO1);
      }
      
      if (n==5000)                    
      {
         //semaforo1
         output_low(VERDE);
         output_low(AMARELO);
         output_high(VERMELHO);
         //semaforo2
         output_low(VERDE1);
         output_high(AMARELO1);
         output_low(VERMELHO1);
      }
      
      if (n==6250)
      {
         n=0;
         //semaforo1
         output_high(VERDE);
         output_low(AMARELO);
         output_low(VERMELHO);
         //semaforo2
         output_low(VERDE1);
         output_low(AMARELO1);
         output_high(VERMELHO1);
           
      }
      
      }

void main()
{
   setup_timer_0 (RTCC_DIV_64|RTCC_INTERNAL | RTCC_8_BIT );
   set_timer0(131);
   enable_interrupts(GLOBAL);
   output_high(VERDE);
   output_high(VERMELHO1);
   enable_interrupts(INT_TIMER0);
   while(true)
{ } 
}

