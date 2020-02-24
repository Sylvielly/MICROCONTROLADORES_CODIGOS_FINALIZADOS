/*MICROCONTROLADORES - ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*PROJETO FINAL - CONTROLE DE AQUECIMENTO DA ÁGUA POR PWM E MONITORACAO DE TEMPERATURA */
//ALUNA: SYLVIELLY S. SOUSA
//MATRICULA: 20162045070410            PROF.: FÁBIO TIMBÓ

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, CPUDIV1,                            //habilitacao dos fusiveis
                                                      //hs = high speed (alta velocidade do oscilador > 3MHz)
                                                      //CPUDIV1 = define a divisao do clock               
                                                     

#use delay(clock=20000000)     //frequencia de operacao

#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)          //habilitacao comunicacao serial
                                                      //baud = banda 
                                                      //xmit = pino de transmissão
                                                      //rcv = pino de recepcao
//inicio configuracao LCD
//#use standart_io(B)           //comentar linha caso biblioteca do lcd seja diferente

#define use_portB_lcd TRUE    //comentar linha caso biblioteca do lcd seja diferente
#define LCD_TYPE 2            //tipo lcd
#include<LCD.c>
//fim configuracao LCD

//inicio programa 
void main(){

               lcd_init();           //inicializacao LCD
while(TRUE){
               char selecao;
               int  valor;
               unsigned int32 velocidade;
               printf("\r\nSelecione rotacao:\r\n");
               printf("    1) 0 \r\n");
               printf("    2) 20 \r\n");
               printf("    3) 50 \r\n");
               printf("    4) 80 \r\n");
               printf("    5) 100 \r\n");
               
               setup_timer_2(T2_DIV_BY_4,249,1);
               set_pwm1_duty(valor);
               lcd_gotoxy(1,1);     //posicao da palavra no LCD
               
               printf(lcd_putc,"\f MOTOR CC");       //imprime palavra no LCD
               lcd_gotoxy(1,2);     //posicao da palavra no LCD
               printf(lcd_putc,"VELOCIDADE=%u",velocidade);       //imprime palavra no LCD
               
               do{
                     selecao=getc();
                 }
               while((selecao<'1')||(selecao>'6'));
               setup_ccp1(CCP_PWM);
               
               switch(selecao){
               
                  case '1': valor = 0;
                            velocidade = 0;
                            break;
                            
                  case '2': valor = 50;
                            velocidade = 20;
                            break;
                            
                  case '3': valor = 125;
                            velocidade = 50;
                            break;
                          
                  case '4': valor = 200;
                            velocidade = 80;
                            break;
                  
                  case '5': valor = 250;
                            velocidade = 100;
                            break;
                
              }                
}
}
