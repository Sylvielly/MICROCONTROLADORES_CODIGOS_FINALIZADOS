/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 02 - CONTROLE DE MOTOR DE PASSO*/
//ALUNA: SYLVIELLY S. SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog
                                           
#define AVANCO  0xF81.0         //B0 
#define RECUO   0xF81.1         //B1
#define SENSOR  0xF81.2         //B2 
#define D4      0xF83.4          
#define D5      0xF83.5         
#define D6      0xF83.6          
#define D7      0xF83.7

void main(){

int REG_1;              //variavel de registrador 1
int REG_2;              //variavel de registrador 1

#asm
//INICIO HABILITACAO DE PULL-UP, ENTRADA [PORTA B] , SAÍDA [PORTA D]
GOTO INICIO


//INICIO DELAY DE 2ms
DELAY_2ms:
MOVLW  0x05   //mover para w = 5d
MOVWF  REG_1 // delay_reg1 = 4d
MOVLW 0xA5       // mover para work =165d
MOVWF REG_2  // delay_reg2 = 255d

LOOP_1: 
DECFSZ REG_1 //decerementa registrador 2 e pula se for zero
goto LOOP_2  
goto EXIT  

LOOP_2:
DECFSZ REG_2 //decerementa registrador 2 e pula se for zero
goto LOOP_2       
goto LOOP_1   

EXIT:
RETURN

//FIM DELAY DE 2ms   

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

//==========================================================================================================================================================

//INICIO LOGICA MOTOR
//INICIO SEQUENCIA_AVANCO
   
BOTAO_TESTE_AVANCO:
   BTFSC AVANCO
   GOTO BOTAO_TESTE_RECUO
   GOTO LINHA_1_AV
   
BOTAO_TESTE_RECUO:
   BTFSC RECUO
   GOTO BOTAO_TESTE_AVANCO
   GOTO LINHA_1_RC
   
LINHA_1_AV:
   BTFSS SENSOR
   CALL TESTE
   BSF D4
   BSF D5
   BCF D6
   BCF D7
   CALL DELAY_2ms
   
LINHA_2_AV:
   BCF D4
   BSF D5
   BSF D6
   BCF D7
   CALL DELAY_2ms
   
LINHA_3_AV:
   BCF D4
   BCF D5
   BSF D6
   BSF D7
   CALL DELAY_2ms
   
LINHA_4_AV:
   BSF D4
   BCF D5
   BCF D6
   BSF D7
   CALL DELAY_2ms
//fim sequencia_avanco

//INICIO SEQUENCIA_AVANCO
   BTFSS RECUO
   GOTO  BOTAO_TESTE_AVANCO
   
LINHA_1_RC:
   BTFSS SENSOR
   CALL TESTE
   BSF D4
   BCF D5
   BCF D6
   BSF D7
   CALL DELAY_2ms
   
LINHA_2_RC:
   BCF D4
   BCF D5
   BSF D6
   BSF D7
   CALL DELAY_2ms
   
LINHA_3_RC:
   BCF D4
   BSF D5
   BSF D6
   BCF D7
   CALL DELAY_2ms
   
LINHA_4_RC:
   BSF D4
   BSF D5
   BCF D6
   BCF D7
   CALL DELAY_2ms
//FIM SEQUENCIA_RECUO
   
   BTFSS AVANCO
   GOTO BOTAO_TESTE_AVANCO
   GOTO LINHA_1_RC
   
TESTE:
   BTFSC SENSOR
   GOTO FIM
   GOTO TESTE
FIM:
   RETURN
   
//FIM LOGICA MOTOR

#endasm
}

