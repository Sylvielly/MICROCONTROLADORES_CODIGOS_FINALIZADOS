/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 03 - CRONOMETRO [DIA:HORA]  */
//ALUNA: SYLVIELLY S. SOUSA

#define BTN_PAUSE PIN_B1
#define BTN_RESET PIN_B2

#include <18f4550.h>
#fuses HS,NOWDT, PUT, BROWNOUT, NOLVP, PROTECT 
#use delay(clock=8000000) 
#byte portE = 0xF84
#byte portD = 0xF83
#byte portA = 0xF80

//PASSO 1: CONFIGURACAO DIGITOS
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

//PASSO 2: CONFIGURACAO DE VARIAVEIS
int16 DIA_DEZ = 0;
int16 DIA_UND = 0;
int16 HORA_DEZ = 0;
int16 HORA_UND = 0;
int16 AUXILIAR_PAUSE = 0;
int CONTA = 0;
int n=0;
int PAUSE = 1;

//PASSO 3: CONFIGURACAO DE TIMERS
#int_timer0 //Identificação da interrupção do Timer 0

void trata_t0()         //função de tratamento da interrupção do Timer 0
{
set_timer0(131+get_timer0());
n++;
   CONTA++;             //Incrementa a variável conta
if (CONTA>4) CONTA = 1; //Se conta > 4, faz conta = 1

switch(conta)           //’Chaveia’ o valor da variável conta
{
      case 1: OUTPUT_D(digito_display[DIA_DEZ]);       //Coloca na Porta D o valor referente ao dígito 0
              OUTPUT_A(0x00);
              OUTPUT_E(0X01);                         //Liga o Display 1 e desliga os demais
              break;
      case 2: OUTPUT_D(digito_display[DIA_UND]);       //Coloca na Porta D o valor referente ao dígito 1
              OUTPUT_E(0X02);                          //Liga o Display 2 e desliga os demais
              break;
      case 3: OUTPUT_D(digito_display[HORA_DEZ]);       //Coloca na Porta D o valor referente ao dígito 2
              OUTPUT_E(0X04);                           //Liga o Display 3 e desliga os demais
              break;
      case 4: OUTPUT_D(digito_display[HORA_UND]);      //Coloca na Porta D o valor referente ao dígito 2
              OUTPUT_E(0x00);
              OUTPUT_A(0X20);                         //Liga o Display 4 e desliga os demais
              break;
}
}

void main(){
//CONFIGURACAO DO TIMER0
setup_timer_0(RTCC_DIV_16|RTCC_INTERNAL|RTCC_8_BIT);
set_timer0(55);
enable_interrupts(GLOBAL);
enable_interrupts(INT_TIMER0);

//CRONOMETRO DD:HH

   while(TRUE)
{
   //calibrar n para 2 minutos
if((n==43)&&(PAUSE))
{
   n=0;
   
  //INICIO LOGICA CRONOMETRO DD:HH
  HORA_UND++; //COMECA INCREMENTANDO DISPLAY DAS UNIDADES  

     if(HORA_UND>9)        //DISPLAY UNID VAI DE 0-9
        {
            HORA_UND = 0;
            HORA_DEZ++;    //SE DISPLAY UNID = 9, ELE ZERA E INCREMENTA DISPLAY DEZ
        }               
        
     if((HORA_DEZ==2)&&(HORA_UND==4))        //COMPARA CONDICOES DOS DISPLAYS DA HORA REFERENTES A DEZENA E UNIDADE RESPECTIVAMENTE
     {
            HORA_UND = 0;                          
            HORA_DEZ = 0;
            DIA_UND++;
               if(DIA_UND>9)
                  {
                     DIA_UND = 0;
                     DIA_DEZ++;   
                  }

            if((DIA_DEZ==3)&&(DIA_UND==0))
         
              {
                  DIA_DEZ = 0;
                  DIA_UND = 0;
                  HORA_DEZ = 0;
                  HORA_UND = 0;   
              }
     }
}

if (input(BTN_RESET)==0)
{
                  DIA_DEZ = 0;
                  DIA_UND = 0;
                  HORA_DEZ = 0;
                  HORA_UND = 0;
}

if(input(BTN_PAUSE)==1)
{
      AUXILIAR_PAUSE = 1;
}

if(input(BTN_PAUSE)==0)
{
      AUXILIAR_PAUSE = 0;
      PAUSE++;
      if(PAUSE == 2) 
         {
            PAUSE=0;   
         }
} //FIM LOGICA BOTAO 'PAUSE'

      } //FIM WHILE



}//FIM MAIN

//SET_TIMER = 55
//N = 104
