/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 01 - CONTROLE DE NÍVEL DE UMA CAIXA D'AGUA SEM CISTERNA*/
//EQUIPE: KARINE MENDES / LINDALVA ALMEIDA / SYLVIELLY SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog
void main()

{

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
   
   movlw 0xE6                 //w = 11100110b
   movwf 0xFD3                //oscilador interno f_clock = 4MHz
                              //desabilita cristal externo (sem cristal e capacitores (A.K.A = menos grana $$$ :D)) 

//FIM HABILITACAO DE PULL-UP, ENTRADA [PORTA B] , SAÍDA [PORTA D]

//INICIO LOOP PRESA
LOOP:
BTFSC 0xF81.0
GOTO L1
BTFSC 0xF81.1
GOTO L1
BSF 0xF83.0
CALL LOOP

L1:
BCF 0xF83.0
CALL LOOP
//FIM LOOP PRESA
#endasm
}
