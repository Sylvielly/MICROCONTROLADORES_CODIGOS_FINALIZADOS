
//TRABALHO 1
//DISCIPLINA: MICROCONTROLADOR
//ALUNA: LINDALVA XAVIER DE ALMEIDA

#include<18f4550.h>
#fuses hs,nowdt,noprotect,nolvp,NOMCLR // quando o oscilador é maior que 3MHz
                                       //não habilita o watchdog
                                       //programa não protegido
                                       //detecçao de tensão
                                       //não energiza o pino 1                                 

void main()
{
#asm
inicio:
movlw 0x00 //habilita pullup
movwf 0xFF1 // intcon2
movlw 0xFF
movwf 0xF93 // trisB-porta B(entrada)
movlw 0x00  
movwf 0xF95 // trisD-porta D(saída)
movlw 0xF6  //w=11110101 
movwf 0xFD3 // oscilador/8MHz/sem cristal e sem capacitor

loop1: //loop da condição para a caixa cheia

BTFSC 0xF81.0 //se B0==0 ele pula 
goto loop2
BTFSC 0xF81.1 // se B1==0 ele pula
goto loop2
BCF 0XF83.0 // se for verdadeiro a bomba vai permanecer desligada
call loop1

loop2: // loop da condição para a caixa vazia
BTFSS 0xF81.0 // se B0==1 ele pula
goto alva
BTFSS 0xF81.1 // se B1==1 ele pula
goto alva
BSF 0xF83.0 // se for verdadeiro vai setar


alva:  //limpar valor

call loop1

#endasm
  

}
