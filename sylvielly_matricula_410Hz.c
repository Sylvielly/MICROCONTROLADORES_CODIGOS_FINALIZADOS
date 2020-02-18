/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
//ALUNA: SYLVIELLY SOUSA

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                           //hs = high speed (alta velocidade do oscilador > 3MHz)
                                           //noprotect = codigo nao protegido (direitos autorais)
                                           //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                           //nolvp = desabilita low voltage pin
                                           //nowtd = desabilita watchdog


void main()                   //funcao principal do programa
{
   int delay_reg1;            //variavel do tipo 'int' 1
   int delay_reg2;            //variavel do tipo 'int' 2
   
   #asm                       //habilitacao da programacao assembly
   
   goto inicio                //ir para label de inicio
   
   Delay2439us:                //label delay 2439us/2 = 1219.5us
                               //
                               //DEC1 = ((1219.5 - 775)772) + 1 = 2
   movlw 0x3                  //'w = 3d'
                              //registrador assume valor 131 decimal
                              //possui duracao de 1us
                              
   movwf delay_reg1           //reg1 = 143d
                              //move valor armazenado em "w" para a variavel criada delay_reg1
   
   movlw 0x8F                 //move valor w=143d
                              
   movwf delay_reg2           //reg2=255d
                              //registrador assume valor 255 decimal
                              //possui duracao de 1us
   loop1:
   DECFSZ delay_reg1          //decrementa 'f' dentro da variavel [delay_reg1] e pula se igualar a zero

   goto loop2                 //feito o loop1, vai para o loop2
   goto exit

   loop2:

   DECFSZ delay_reg2          // decrementa 'f' dentro da variavel [delay_reg2]e pula se igualar a zero
   goto loop2                 //continua executando loop2
   goto loop1                 //caso o 'delay_reg2' chegue a zero ele ira pular a linha 'goto loop2' e fará o loop1

   Exit:                      
   RETURN
   
   inicio:
   
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
   movwf 0xFD3                //Oscilador interno [OSCCON] f_clock = 4MHz 
                              //desabilita cristal externo (sem cristal e capacitores (A.K.A = menos grana $$$ :D)) 
   
   
   loop:
   clrf 0xF83                 //limpa porta D
   call Delay2439us            //chama subrotina de delay 100ms       
                              //funcao 'CALL' utiliza 2 ciclos de maquina  
                              //funcoes que "pulam" utilizam 2 ciclos de maquina 
   
   movlw 0xFF                 //w = FFh             
   movwf 0XF83                //porta D = 11111111b
                              //joga '1' na porta D
  
   call Delay2439us            //vai pra subrotina Delay100ms
   goto loop                  //vai pra subrotina loop  

   #endasm


}

