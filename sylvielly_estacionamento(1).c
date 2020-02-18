/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 03 - CONTROLE DE ESTACIONAMENTO 10 VAGAS EM C*/
//ALUNA: SYLVIELLY S. SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, CPUDIV1, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog

                                           
//DEFINICOES DE PINOS PARA CANCELA DE ENTRADA                                           
#define SENSOR_0      pin_b0       //sensor de abertura da cancela    
#define SENSOR_1      pin_b1       //sensor em que indica que o carro está na cancela 
#define CANCELA_ENT   pin_d0      
#define CHEIO         pin_d7  
//DEFINICOES DE PINOS PARA CANCELA DE SAIDA                                           
#define SENSOR_2        pin_b2         
#define SENSOR_3        pin_b3       
#define CANCELA_SAIDA   pin_d1     

#use delay(clock=20000000)        //CLOCK = 4MHz   

void main()

{

//DECLARACAO DE VARIAVEIS
int VAGAS_OCUPADAS=0;           //estacionamento vazio 
int ESTADO_CANCELA_ENTRADA=0;           
int ESTADO_CANCELA_SAIDA=0;
int AUX_CANCELA_ENT=0;
int AUX_CANCELA_SAIDA=0;

port_b_pullups(TRUE);
//INICIO WHILE
while(TRUE){


//INICIO LOGICA CANCELA DE ENTRADA   
if((input(SENSOR_0)==0)&&(VAGAS_OCUPADAS<=9))                   //testa sensor de entrada [B0==0] e se quantidade de vagas é <=5
         {
               output_high(CANCELA_ENT);                               //se B0==0, abre cancela de entrada
               AUX_CANCELA_ENT=1;                              //variavel criada para 
         }
         
if((AUX_CANCELA_ENT==1)&&(input(SENSOR_1)==0))           //captura estado da cancela [se cancela_entrada==1 e sensor_1==0]
         {   
               ESTADO_CANCELA_ENTRADA=1;
         }
         
if((ESTADO_CANCELA_ENTRADA==1)&&(input(SENSOR_1)==1))                    //comparacao do estado da cancela para abaixa-la
  {
               delay_ms(500);
               if((ESTADO_CANCELA_ENTRADA==1)&&(input(SENSOR_1)==1))
               {
                  output_low(CANCELA_ENT);      //desce cancela
                  VAGAS_OCUPADAS++;              //incrementa vagas
                  ESTADO_CANCELA_ENTRADA=0;
                  AUX_CANCELA_ENT=0;
               }
  }
          
         
if (VAGAS_OCUPADAS==5)
         {
             output_high(CHEIO);         //liga led indicando que nao ha mais vagas
         }


//FIM LOGICA CANCELA DE ENTRADA

//INICIO LOGICA CANCELA DE SAIDA
         if((input(SENSOR_2)==0)&&(VAGAS_OCUPADAS>0))                   //testa sensor de saida [B2==0] e se quantidade de vagas é maior que zero
         {
               output_high(CANCELA_SAIDA);                               //se B2==0, abre cancela de saida   
               AUX_CANCELA_SAIDA=1;
         }
         
         if((AUX_CANCELA_SAIDA==1)&&(input(SENSOR_3)==0))           //captura estado da cancela [se cancela_saida==1 e sensor_3==0]
         {   
               ESTADO_CANCELA_SAIDA=1;
         }
         
         if((ESTADO_CANCELA_SAIDA==1)&&(input(SENSOR_3)==1))                    //comparacao do estado da cancela para abaixa-la
         {
               delay_ms(500);
               if((ESTADO_CANCELA_SAIDA==1)&&(input(SENSOR_3)==1))
               {
                  output_low(CANCELA_SAIDA);      //desce cancela
                  VAGAS_OCUPADAS--;              //decrementa vagas
                  ESTADO_CANCELA_SAIDA=0;
                  AUX_CANCELA_SAIDA=0;
               }
          }
          
         
         if (VAGAS_OCUPADAS==0)
         {
             output_low(CHEIO);         //desliga led indicando que ha mais vagas
         }
         
//FIM LOGICA CANCELA DE SAIDA
}     //FIM WHILE

}     //FIM PROGRAMA



