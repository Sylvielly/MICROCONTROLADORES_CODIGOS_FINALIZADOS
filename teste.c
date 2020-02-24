//Programa estacionamneto

#include <18f4550.h>
//noprotect permite capturar programa pelo pic
//hs acima de 8mhz, na utliza��o do cristal externo
//nowdt testa se est� pedindo para executar alguma coisa(c�o de guarda)
//nomclr para utilizar o clock interno
//nolvp ele precisa de alta tens�o aplicado no master clear(barrado)
#fuses hs,nowdt,noprotect,nolvp,NOMCLR
#define A 0xF81.0  //A � igual ao pino zero da porta B(F81)
#define B 0xF81.1  //B � igual ao pino um da porta B(F81)
#define C 0xF83.0  //C � igual ao pino zero da porta D(F83)
#define D 0xF83.1  //D � igual ao pino um da porta D(F83)

void main() {

#asm  
//------W recebe valor e passa para o FF1 que � INCON2-------------------------
   //S� a porta B tem registrador de PULL-UP
 movlw  0x00  // 00h= pullup habilitado;80h=pullup desabilitado.
 movwf  0xFF1 //intcon2=00h
//-----------------------------------------------------------------------------

// A e B j� est�o setados como 1

//--W recebe a configura��o dos pinos para entrada e passa para F93 que � o TRISB--
 movlw  0xFF  //w=11111111b
 movwf  0xF93  //trisbB=11111111b
//-----------------------------------------------------------------------------

//--W recebe a configura��o dos pinos para saida e passa para F95 que � TRISD--
 movlw  0x00 //w=00000000b
 movwf  0xF95 // trisD=00000000b 
//-----------------------------------------------------------------------------

movlw  0xE6 //w=11100110b
movwf  0xFD3


L0:
   BTFSC A  //Se A for zero pula (condi��o 0 = bot�o apertado / condi��o 1 = bot�o solto)
   GOTO L1
   BSF C    //Se A zero, C � setado para 1(cancela abre)

L1: 
   BTFSS C  //Se C for um pula(condi��o 0 = cancela fechada / condi��o 1 = cancela aberta)
   GOTO L2
   BTFSS B  //Se B for um pula (condi��o 0 = carro n�o passou / condi��o 1 = carro passando)
   GOTO L2
   BSF D    //Se A e B for um, D � setado para 1(ativa memoria com carro) 
   
L2: 
   BTFSS D  //Se D for um pula (condi��o 0 = memoria desabilitada sem carro / condi��o 1 = ativa memoria com carro)
   GOTO FIM
   BTFSC B  //Se B for um pula (condi��o 0 = carro j� passou / condi��o 1 = carro ainda n�o passou)
   GOTO FIM
   BCF D    //Se carro passou, D � setado para 0 (memoria limpa)
   BCF C    //Se carro passou, C � setado para 0 (fecha cancela)

FIM: // Reiniciar LOOP
   GOTO L0

#endasm
}

