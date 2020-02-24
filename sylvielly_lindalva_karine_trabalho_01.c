/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 01 - CONTROLE DE N�VEL DE UMA CAIXA D'AGUA SEM CISTERNA*/
//EQUIPE: KARINE MENDES / LINDALVA ALMEIDA / SYLVIELLY SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog
                                           
#define A 0xF93.0  //A � igual ao pino zero da porta B(F93)
#define B 0xF93.1  //B � igual ao pino um da porta B(F93)
#define C 0xF95.0  //C � igual ao pino zero da porta D(F95)
#define D 0xF95.1  //D � gual ao pino um da porta D (F95)

void main()

{

#asm
//INICIO HABILITACAO DE PULL-UP, ENTRADA [PORTA B] , SA�DA [PORTA D]
   
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
   
   movlw 0xE6                 //w = 11100110b
   movwf 0xFD3                //oscilador interno f_clock = 8MHz
                              //desabilita cristal externo (sem cristal e capacitores (A.K.A = menos grana $$$ :D)) 

//FIM HABILITACAO DE PULL-UP, ENTRADA [PORTA B] , SA�DA [PORTA D]

//INICIO LOGICA CAIXA D'AGUA
L0:
   BTFSC A  //Se A for zero(condi��o 0 = Caixa cheia[bot�o apertado] / condi��o 1 = caixa vazia[bot�osolto])
   GOTO L1
   BTFSC B  //Se B for zero(condi��o 0 = Caixa cheia[bot�o apertado] / condi��o 1 = caixa vazia[bot�osolto])
   GOTO L1
   BCF C    //Se A e B for zero[caixa cheia], C � restado para 0(desliga valvula)
   GOTO L2

L1: 
   BTFSS A  //Se A for um (condi��o 0 = Caixa cheia[bot�o apertado] / condi��o 1 = caixa vazia[bot�osolto]
   GOTO L2
   BTFSS B  //Se B for um(condi��o 0 = Caixa cheia[bot�o apertado] / condi��o 1 = caixa vazia[bot�osolto])
   GOTO L2
   BSF C //Se A ou B for um, C � setado para um(liga valvula) 
   
L2: // Reiniciar LOOP
   GOTO L0

//FIM LOGICA CAIXA D'AGUA
#endasm
}

