/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*TRABALHO 01 - CONTROLE DE ESTACIONAMENTO*/
//ALUNA: SYLVIELLY S. SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog
                                           
#define BOTAO 0xF81.0         //B0 
#define SENSOR 0xF81.1        //B1
#define CANCELA 0xF83.0       //D0
#define VAGA 0xF83.1          //D1
#define FLAG 0xF83.2          //D2
                                           
void main()

{
int VAGAS = 10;           //contador de vagas, estacionamento inicia cheio
int REG_1;              //variavel de registrador 1
int REG_2;              //variavel de registrador 1

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

//INICIO ATRASO DE 2s
DELAY:                 //LABEL DE DELAY DE 2s
   movlw 100000
   movwf REG_1
   movlw 100000
   movwf REG_2
REC:
   movlw 100000      //RECARREGANDO O REG_1
   movwf REG_1

LOOP_1:               // TEMPO DO CICLO = 4 x 1/FREQUÊNCIA   ->   TEMPO DO CICLO = 4 x 1/4000000 = 1us
                     // PARA TERMOS UM ATRASO DE 1s, SERÃO NECESSÁRIOS 10^12 CICLOS DE MÁQUINA
                     // TEMPO DESEJADO = (10^12)*0,000001 = 1s
   DECFSZ REG_1 // 1 CICLO          10 CICLOS * 100000 = 1000000 CICLOS
   NOP //1 CLICO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   goto LOOP_1        // 2 CICLOS
      
LOOP_2:
   DECFSZ REG_2 // 1 CICLO             1000000 CICLOS * 100000 = 1000000000000 CICLOS NECESSÁRIO PARA TERMOS UM ATRASO DE 1S.  
                     // NÃO FORAM CONSIDERADOS OS 3 CICLOS GASTOS PELO LOOP2
   goto REC
   goto EXIT         //                     TEREMOS UMA DIFERENÇA DE 0,003s ou 3ms

EXIT:
   BTFSC SENSOR        //VERIFICAÇÃO APÓS 1s, CASO O SENSOR VOLTE A SER ACIONADO, VOLTE PARA O LAÇO DO SENSOR LB
   GOTO  D_CANCELA      //CASO O SENSOR NÃO VOLTE A SER ACIONADO, DESLIGUE A CANCELA
   GOTO  L2
   RETURN
//FIM ATRASO DE 2s
   
//INICIO LOGICA FUNCIONAMENTO ESTACIONAMENTO COM 10 VAGAS 

VAZIO:
   BCF VAGA      //MATEM LED AMARELO APAGADO

L0:
   BTFSC BOTAO    //VERIFICA SE O BOTÃO FOI ACIONADO, ISTO É, SE ESTÁ SETADO COMO 0
   GOTO  L1       //EM CASO NEGATIVO, CHAMA L1
   BSF   CANCELA   //EM CASO POSITIVO, ATIVA CANCELA
  
L1:
   BTFSS CANCELA  //PULA, SE A CANCELA ESTIVER ACIONADA
   GOTO  END
   BTFSC SENSOR  //PULA SE O SENSOR ESTIVER ACIONADO
   GOTO  L1
   GOTO  L2    //CASO O SENSOR ESTEJA ACIONADO, VÁ PRA L2
   
L2:
   BTFSS SENSOR     //O PROGRAMA SÓ IRÁ SAIR DE L2 CASO O SENSOR VOLTE A FICAR DESACIONADO (CARRO PASSOU)
   GOTO  L2
   GOTO  DELAY    //CASO O CARRO PASSE, ESPERE 1s
   
D_CANCELA:
   BCF      CANCELA  //DESACIONA A CANCELA
   DECFSZ   VAGAS    //DECREMENTA A QUANTIDADE DE VAGAS DO ESTACIONAMENTO
   GOTO     INICIO   //CASO 
   GOTO     CHEIO
   
CHEIO:
   BSF      VAGA   //DESLIGA O LED INDICADOR DE VAGAS DO ESTACIONAMENTO
      
END:
   GOTO     L0
   //FIM LOGICA FUNCIONAMENTO ESTACIONAMENTO COM 10 VAGAS

#endasm
}

