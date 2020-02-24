#include <18f4550.h>
#fuses hs,nowdt,noprotect,nolvp,NOMCLR   //oscilador maior de 3MHz,watchdog desabilitado, não é protegido, não habilita pino 1
void main()
{
int tempo_1;   //declaração de variáveis - inteiro delay_reg1
int tempo_2;   //declaração de variáveis - inteiro delay_reg2

#asm
goto inicio       // vai para o ínico
Delay2000us:
movlw  0x05   //mover para w = 5d
movwf  tempo_1 // delay_reg1 = 4d
movlw 0xA5       // mover para work =165d
movwf tempo_2  // delay_reg2 = 255d

loop1: 
DECFSZ tempo_1 // decrementa delay_reg 1 e skip se zero
goto loop2  //va para loop 2
goto exit  // VA PARA EXIT

loop2:
DECFSZ tempo_2 //decerementa delay_reg2 e skip se zero
goto loop2       // va para loop 2
goto loop1       // va para loo1

Exit:
RETURN
inicio:
movlw   0x00      // Move literal para o registrador work 00h - pullup habilitado, 80h - pullup desabilitado
movwf  0xFF1     // move 00h -pullup habilitado  do registrador work para o inticon2; intcon2 = 00h
movlw   0xFF      // move para w = 11111111b
movwf  0xF93     // move 11111111b do w para o trisb= 11111111b / habilitou como entrada
movlw   0x00      // move 00000000b para o work
movwf   0xF95     // move 00000000b para trisd, trisd=00000000b / habilitou como saída
movlw   0xE6      // w =11100110
movwf  0xFD3     // oscilador 4mhz sem cristal e capacitor


teste_1:
BTFSC 0xF81.0 //TESTAR SE B0==0
GOTO teste2 // vai para o teste 2
GOTO A1

teste2:
BTFSC 0xF81.1 // testar se b1==0
GOTO teste_1
GOTO R1

A1:
BTFSS 0xF81.2 
call sensor
BSF 0XF83.4 //SETAR D4
BSF 0XF83.5 //SETAR D5
BCF 0XF83.6 // LIMPAR D6
BCF 0XF83.7 // LIMPAR D7
call Delay2000us
A2:
BCF 0XF83.4 //LIMPAR D4
BSF 0XF83.5 // SETAR D5
BSF 0XF83.6 // SETAR D6
BCF 0XF83.7 // limpar D7
call Delay2000us
A3:
BCF 0XF83.4 //LIMPAR D4
BCF 0XF83.5 //limpar D5
BSF 0XF83.6 //SETAR D6
BSF 0XF83.7 //SETAR D7
call Delay2000us
A4:
BSF 0XF83.4 //SETAR D4
BCF 0XF83.5 //limpar D5
BCF 0XF83.6 //limpar D6
BSF 0XF83.7 //SETAR D7
call Delay2000us
BTFSS 0XF81.1 //TESTAR B1==1
goto teste_1
goto A1


R1:
BTFSS 0xF81.2 
call sensor
BSF 0XF83.4 //SETAR D4
BCF 0XF83.5 //limpar D5
BCF 0XF83.6 //limpar D6
BSF 0XF83.7 //SETAR D7
call Delay2000us
R2:
BCF 0XF83.4 //LIMPAR D4
BCF 0XF83.5 //limpar D5
BSF 0XF83.6 //SETAR D6
BSF 0XF83.7 //limpar D7
call Delay2000us
R3:
BCF 0XF83.4 //LIMPAR D4
BSF 0XF83.5 // SETAR D5
BSF 0XF83.6 // SETAR D6
BCF 0XF83.7 // limpar D7
call Delay2000us
R4:
BSF 0XF83.4 //SETAR D4
BSF 0XF83.5 //SETAR D5
BCF 0XF83.6 // LIMPAR D6
BCF 0XF83.7 // LIMPAR D7
call Delay2000us
BTFSS 0XF81.0 //TESTAR B0==0
GOTO teste_1
Goto R1

sensor:
BTFSC 0xF81.2
goto exit1
goto sensor

exit1:
RETURN

#endasm
}

