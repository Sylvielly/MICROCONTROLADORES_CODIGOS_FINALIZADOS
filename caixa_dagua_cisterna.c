// ==================== Engenharia de Controle e Automacao ===================== 

// ========== Trabalho 2 ========== Microcontroladores ========== Prof. Fabio 

// Arquivo 1: Caixa d'agua e cisterna com tres sensores
// Aluna: Sylvielly Silva de Sousa
// Matricula: 20162045070410                           //Semestre: 2018.1

// ======================= // ======================= // =======================
//   

#include <18f4550.h>                        // inclusao da biblioteca PIC18F4550
#fuses hs, nowdt,  noprotect, nolvp, NOMCLR

//nowdt -- desabilita o watch dog
//noprotect -- desabilita protecao do programa, no qual permite a leitura do mesmo pelo PIC
//NOMCLR -- desabilita o master clear

// ======================= // ======================= // =======================

// Definicoes pinos

#define pino_0_A 0xF81.0  //porta B(F81) pino 0
#define pino_1_B 0xF81.1  //porta B(F81) pino 1
#define pino_0_C 0xF83.0  //porta D(F83) pino 0
#define pino_2_D 0xF81.2  //porta B(F81) pino 2

// ======================= // ======================= // =======================

//inicio do programa

void main()

{

                  #asm     //inicia a programacao em assembly

// ====================== Configuracao dos registradores =======================

           movlw  0x00        //habilita o PULL-UP [00h]
           movwf  0xFF1       //recebe o valor de 00h para o INTCON2 [FF1]
           
           movlw  0xFF        //w recebe configuracao 11111111b
           movwf  0xF93       //registrador f recebe o valor F93 (TRIS B = 11111111b)
           
           movlw  0x00        //w recebe configuracao 00000000b
           movwf  0xF95       //registrador f recebe o valor F95 (TRIS D=00000000b)
           
           movlw  0xE6        //w recebe configuracao 11100110b
           movwf  0xFD3       //registrador f recebe o valor FD3 (OSCON = 11100110b)
           
// ======================== INICIO PROGRAMA CISTERNA ===========================          

Linha_zero:
    
    BTFSS pino_2_D         //PINO D PARA CONDIÇÕES DA CISTERNA, SE D = 0 CISTERNA CHEIA
    GOTO  Linha_um
    BCF   pino_0_C
    GOTO  Linha_quatro

Linha_um:
    
    BTFSC pino_0_A         //Se A = 0, CAIXA CHEIA
    GOTO  Linha_dois
    BTFSC pino_1_B         //Se B = 0, CAIXA CHEIA
    GOTO  Linha_dois
    BCF   pino_0_C         //Se A = 0 e B = 0, C volta para 0 [DESLIGA VÁLVULA]
    GOTO  Linha_quatro

Linha_dois: 
    
    BTFSS pino_0_A         //Se A = 1, CAIXA SECA
    BTFSS pino_1_B         //Se B = 1, CAIXA SECA
    GOTO  Linha_quatro
    BSF   pino_0_C         //Se A = 1 e B = 1, C vai para 1 [LIGA VÁLVULA]    
   
Linha_quatro: // Reiniciar LOOP
   
   GOTO Linha_zero
   
// ========================== FIM PROGRAMA CISTERNA ============================

                  #endasm     //finaliza a programacao em assembly

}
