//Programa estacionamneto

#include <18f4550.h>
//noprotect permite capturar programa pelo pic
//hs acima de 8mhz, na utlização do cristal externo
//nowdt testa se está pedindo para executar alguma coisa(cão de guarda)
//nomclr para utilizar o clock interno
//nolvp ele precisa de alta tensão aplicado no master clear(barrado)
#fuses hs,nowdt,noprotect,nolvp,NOMCLR
#define A 0xF81.0  //A é igual ao pino zero da porta B(F81)
#define B 0xF81.1  //B é igual ao pino um da porta B(F81)
#define C 0xF83.0  //C é igual ao pino zero da porta D(F83)
#define D 0xF83.1  //D é igual ao pino um da porta D(F83)

void main() {

#asm  
//------W recebe valor e passa para o FF1 que é INCON2-------------------------
   //Só a porta B tem registrador de PULL-UP
 movlw  0x00  // 00h= pullup habilitado;80h=pullup desabilitado.
 movwf  0xFF1 //intcon2=00h
//-----------------------------------------------------------------------------

// A e B já estão setados como 1

//--W recebe a configuração dos pinos para entrada e passa para F93 que é o TRISB--
 movlw  0xFF  //w=11111111b
 movwf  0xF93  //trisbB=11111111b
//-----------------------------------------------------------------------------

//--W recebe a configuração dos pinos para saida e passa para F95 que é TRISD--
 movlw  0x00 //w=00000000b
 movwf  0xF95 // trisD=00000000b 
//-----------------------------------------------------------------------------

movlw  0xE6 //w=11100110b
movwf  0xFD3


L0:
   BTFSC A  //Se A for zero pula (condição 0 = botão apertado / condição 1 = botão solto)
   GOTO L1
   BSF C    //Se A zero, C é setado para 1(cancela abre)

L1: 
   BTFSS C  //Se C for um pula(condição 0 = cancela fechada / condição 1 = cancela aberta)
   GOTO L2
   BTFSS B  //Se B for um pula (condição 0 = carro não passou / condição 1 = carro passando)
   GOTO L2
   BSF D    //Se A e B for um, D é setado para 1(ativa memoria com carro) 
   
L2: 
   BTFSS D  //Se D for um pula (condição 0 = memoria desabilitada sem carro / condição 1 = ativa memoria com carro)
   GOTO FIM
   BTFSC B  //Se B for um pula (condição 0 = carro já passou / condição 1 = carro ainda não passou)
   GOTO FIM
   BCF D    //Se carro passou, D é setado para 0 (memoria limpa)
   BCF C    //Se carro passou, C é setado para 0 (fecha cancela)

FIM: // Reiniciar LOOP
   GOTO L0

#endasm
}

