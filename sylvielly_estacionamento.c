/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 02 - CONTROLE DE ESTACIONAMENTO 10 VAGAS*/
//ALUNA: SYLVIELLY S. SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog
                                           
#define BOTAO  0xF81.0         //B0 
#define SENSOR 0xF81.1        //B1
#define CANCELA 0xF83.0       //D0
#define VAGA 0xF83.1          //D1
#define FLAG 0xF83.2          //D2
                                           
main()

{
int VAGAS = 10;           //contador de vagas, estacionamento inicia cheio

#asm
//INICIO HABILITACAO DE PULL-UP, ENTRADA [PORTA B] , SAÍDA [PORTA D]

INICIO:
   
   movlw 0x00                 //move literal para o registrador 'w'
                              //habilita pull-up [00h]
                              //desabilita pull-up [80h]
   movwf 0xFF1                //move o valor de '0x00' para registrador 'f'
                              //FF1h = INTCON2
                    
   movlw 0xFF                 //w = 11111111b                  
                              //valor do registrador 'w' = 1
   
   movwf 0xF93                //joga valor do registrador 'w=1' para TRISB = 11111111b (setando como entrada)
   
   movlw 0x00                 //move literal para o registrador 'w'
   movwf 0xF95                //joga valor do registrador 'w=1' para TRISD = 00000000b (setando como saida) 
   
   movlw 0xE6                 //w = 11110110b
   movwf 0xFD3                //oscilador interno f_clock = 4MHz
                              //desabilita cristal externo (sem cristal e capacitores (A.K.A = menos grana $$$ :D)) 

//FIM HABILITACAO DE PULL-UP, ENTRADA [PORTA B] , SAÍDA [PORTA D]

   
//INICIO LOGICA ESTACIONAMENTO
VAZIO:
   BCF   VAGA           //led de indicacao permanece apagado
   
CONDICAO_1:              //label de verificacao de sensor de entrada
   BTFSC BOTAO          //testa se B0=0
   GOTO  CONDICAO_2     //vai para teste da cancela
   BTFSS VAGA
   BSF   CANCELA        //se B0=0, cancela abre (D0=1)
   
CONDICAO_2:             //label de teste da cancela
   BTFSS CANCELA        //testa se D0=1
   GOTO  END
   BTFSC SENSOR         //caso D0=1, testa se o sensor B1=0
   GOTO  CONDICAO_2     //caso B!=0, volta a testar cancela
     
CONDICAO_3:
   BTFSS SENSOR         //testa se sensor B1=0, se sim pula
   GOTO  CONDICAO_3
   BSF   FLAG           //se sensor B1=0, seta flag D1=1
/*   GOTO  DELAY //(CASO HAJA)*/
   
CONDICAO_4:
   BCF   SENSOR         //desaciona sensor B1
   BCF   FLAG           //apaga valor da flag
   BCF   CANCELA        //abaixa a cancela
   DECFSZ VAGAS         //decrementa vaga, se for zero, pula
   GOTO  INICIO
   GOTO  CHEIO          //vai para label cheio e seta led de aviso 
   
CHEIO:
   BSF   VAGA           //liga o led indicador de vagas
   
END:
   GOTO  CONDICAO_1
//FIM LOGICA ESTACIONAMENTO

#endasm
}

