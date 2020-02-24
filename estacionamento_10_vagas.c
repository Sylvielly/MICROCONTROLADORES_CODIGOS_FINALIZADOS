// ==================== Engenharia de Controle e Automacao ===================== 

// ========== Trabalho 2 ========== Microcontroladores ========== Prof. Fabio 

// Arquivo 2: Estacionamento para 10 vagas
// Aluna: Sylvielly Silva de Sousa
// Matricula: 20162045070410                           //Semestre: 2018.1

// ======================= // ======================= // =======================
//   

#include <18f4550.h>
#fuses hs,nowdt,noprotect,nolvp,NOMCLR
#define BTN 0xF81.0     //IDENTIFICA A PORTA 0 DA ENTRADA B
#define SENS 0xF81.1    //IDENTIFICA A PORTA 1 DA ENTRADA B
#define CANC 0xF83.0    //IDENTIFICA A PORTA 0 DA ENTRADA D
#define VAG 0xF83.1     //IDENTIFICA A PORTA 1 DA ENTRADA D
#define MEM 0xF83.2     //IDENTIFICA A PORTA 2 DA ENTRADA D
void main()
{

      int conta_vagas = 10;
      int delay_reg1;
      int delay_reg2;

      #asm 

goto inicio

delay_2s:
   movlw 100000
   movwf delay_reg1
   movlw 100000
   movwf delay_reg2

aux:
   movlw 100000      //RECARREGANDO O delay_reg1
   movwf delay_reg1

loop1:               // TEMPO DO CICLO = 4 x 1/FREQUÊNCIA   ->   TEMPO DO CICLO = 4 x 1/4000000 = 1us
                     // PARA TERMOS UM ATRASO DE 1s, SERÃO NECESSÁRIOS 10^12 CICLOS DE MÁQUINA
                     // TEMPO DESEJADO = (10^12)*0,000001 = 1s
   DECFSZ delay_reg1 // 1 CICLO          10 CICLOS * 100000 = 1000000 CICLOS
   NOP //1 CLICO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   NOP //1 CICLO
   goto loop1        // 2 CICLOS
      
loop2:
   DECFSZ delay_reg2 // 1 CICLO             1000000 CICLOS * 100000 = 1000000000000 CICLOS NECESSÁRIO PARA TERMOS UM ATRASO DE 1S.  
                     // NÃO FORAM CONSIDERADOS OS 3 CICLOS GASTOS PELO LOOP2
   goto aux          // 2 CICLOS            QUE AO FINAL DARÁ UMA DIFERENÇA DE 750 CICLOS. SE MULTIPLICADO POR 4us
   goto exit         //                     TEREMOS UMA DIFERENÇA DE 0,003s ou 3ms

exit:
   BTFSC SENS        //VERIFICAÇÃO APÓS 1s, CASO O SENSOR VOLTE A SER ACIONADO, VOLTE PARA O LAÇO DO SENSOR LB
   GOTO  D_CANC      //CASO O SENSOR NÃO VOLTE A SER ACIONADO, DESLIGUE A CANCELA
   GOTO  LB
   RETURN

inicio:

//-----------CONFIGURACOES INICIAS DE PORTAS E PULL-UPS-------------------------
movlw  0x00  // 00h= pullup habilitado;80h=pullup desabilitado.
movwf  0xFF1 //intcon2=00h
movlw  0xFF  //w=11111111b
movwf  0xF93  //trisbB=11111111b
movlw  0x00 //w=00000000b
movwf  0xF95 // trisD=00000000b 
movlw  0xE6 //w=11100110b
movwf  0xFD3 //4MHZ
//-----------------------------------------------------------------------------

VAZIO:
   BCF VAG      //MATEM LED AMARELO APAGADO

L0:
   BTFSC BTN    //VERIFICA SE O BOTÃO FOI ACIONADO, ISTO É, SE ESTÁ SETADO COMO 0
   GOTO  L1     //EM CASO NEGATIVO, CHAMA L1
   BSF   CANC   //EM CASO POSITIVO, ATIVA CANCELA
  
L1:
   BTFSS CANC  //PULA, SE A CANCELA ESTIVER ACIONADA
   GOTO  FIM
   BTFSC SENS  //PULA SE O SENSOR ESTIVER ACIONADO
   GOTO  L1
   GOTO  LB    //CASO O SENSOR ESTEJA ACIONADO, VÁ PRA LB
   
LB:
   BTFSS SENS              //O PROGRAMA SÓ IRÁ SAIR DE LB CASO O SENSOR VOLTE A FICAR DESACIONADO (CARRO PASSOU)
   GOTO  LB
   GOTO  delay_2s          //CASO O CARRO PASSE, ESPERE 1s
   
D_CANC:
   BCF      CANC          //DESACIONA A CANCELA
   DECFSZ   conta_vagas   //DECREMENTA A QUANTIDADE DE VAGAS DO ESTACIONAMENTO
   GOTO     inicio       //CASO 
   GOTO     CHEIO
   
CHEIO:
   BSF      VAG         //DESLIGA O LED INDICADOR DE VAGAS DO ESTACIONAMENTO
      
FIM:
   GOTO     L0
   
#endasm
}
