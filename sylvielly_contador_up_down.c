/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 03 - CONTADOR UP / DOWN */
//ALUNA: SYLVIELLY S. SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, protect, nolvp,           //habilitacao dos fusiveis
                                                      //hs = high speed (alta velocidade do oscilador > 3MHz)
                                                      //noprotect = codigo nao protegido (direitos autorais)
                                                      //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                                      //nolvp = desabilita low voltage pin
                                                      //nowtd = desabilita watchdog

#define BTN_UP    pin_b0
#define BTN_DOWN  pin_b2 

#use delay(clock=8000000)
#byte portE = 0xF84
#byte portD = 0xF83
#byte portA = 0xF80

int digito_display[10]= { 0b00111111,
                          0b00000110,
                          0b01011011,
                          0b01001111,
                          0b01100110,
                          0b01101101,
                          0b01111101,
                          0b00000111,
                          0b01111111,
                          0b01101111
                };                             

int16 display_und;
int16 display_dez = 0 ;
int conta = 0;
int d1 = 0;
int d2 = 0;
int variavel_auxiliar_up = 0;
int variavel_auxiliar_down = 0;

#int_timer0  //Identificação da interrupção do Timer 0
void trata_t0()           //função de tratamento da interrupção do Timer 0
{
set_timer0(131+get_timer0());
//inicio saida displays
 
conta++;                    //Incrementa a variável conta

if (conta>4) conta = 1;        //Se conta > 4, faz conta = 1

switch(conta)              //’Chaveia’ o valor da variável conta
         {
              case 1: OUTPUT_D(digito_display[d1]);   //Coloca na Porta D o valor referente ao dígito 0
                      OUTPUT_A(0x00);
                      OUTPUT_E(0X01);     //Liga o Display 1 e desliga os demais
                      break;
                      
              case 2: OUTPUT_D(digito_display[d2]);   //Coloca na Porta D o valor referente ao dígito 1
                      OUTPUT_E(0X02);     //Liga o Display 2 e desliga os demais
                      break;
                      
              case 3: OUTPUT_D(digito_display[display_dez]);   //Coloca na Porta D o valor referente ao dígito 2
                      OUTPUT_E(0X04);     //Liga o Display 3 e desliga os demais
                      break;
                      
              case 4: OUTPUT_D(digito_display[display_und]);   //Coloca na Porta D o valor referente ao dígito 2
                      OUTPUT_E(0x00);
                      OUTPUT_A(0X20);     //Liga o Display 4 e desliga os demais
                      break;
         }
//fim saida displays
}

void main(){

//
setup_timer_0(RTCC_DIV_16|RTCC_INTERNAL|RTCC_8_BIT);
set_timer0(131);
enable_interrupts(GLOBAL);
enable_interrupts(INT_TIMER0);

while(TRUE){

if(input(BTN_UP)==0)            //em logica pull-up
//INICIO LOGICA DISPLAY BOTAO UP  
   {
     variavel_auxiliar_up = 1;
   }
  if((input(BTN_UP)==1)&&(variavel_auxiliar_up==1))       
    {    
         variavel_auxiliar_up = 0;
         display_und++;
         if (display_und>9)
            {
               display_und = 0;
            }
       
  } //fim logica display botao UP 
  
//INICIO LOGICA DISPLAY BOTAO DOWN  
if(input(BTN_DOWN)==0)
   {
     variavel_auxiliar_down = 1;
   }
//inicio logica display botao DOWN
   if((input(BTN_DOWN)==1)&&(variavel_auxiliar_down==1))
   {
       variavel_auxiliar_down = 0;
       if(display_und>0)
            {
               display_und--;
            }
   }

   }
}
