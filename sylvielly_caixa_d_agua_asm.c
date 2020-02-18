/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 01 - CONTROLE DE NÍVEL DE UMA CAIXA D'AGUA SEM CISTERNA*/
//ALUNA: SYLVIELLY S. SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog
                                           
#define B0 0xF81.0 
#define B1 0xF81.1
#define D0 0xF83.0
                                           
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
   
   movlw 0xF6                 //w = 11110110b
   movwf 0xFD3                //oscilador interno f_clock = 4MHz
                              //desabilita cristal externo (sem cristal e capacitores (A.K.A = menos grana $$$ :D)) 

//FIM HABILITACAO DE PULL-UP, ENTRADA [PORTA B] , SAÍDA [PORTA D]

//INICIO LOGICA CAIXA D'AGUA
LOOP:
BTFSC B0        //PINO 0 DA PORTA B - B0                        
goto L1
BTFSC B1        //PINO 1 DA PORTA B - B1
goto L1
BCF D0          //PINO 0 DA PORTA D - D0 - NÃO LIGA BOMBA

L1:
BTFSS B0        //PINO 0 DA PORTA B - B1
goto L2
BTFSS B1        //PINO 1 DA PORTA B - B0
goto L2
BSF D0          //PINO 0 DA PORTA D - D0 - LIGA A BOMBA

L2:
goto LOOP //retorna pro programa 

//FIM LOGICA CAIXA D'AGUA
#endasm
}

