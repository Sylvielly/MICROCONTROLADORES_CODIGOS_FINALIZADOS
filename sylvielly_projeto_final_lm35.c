/*MICROCONTROLADORES - ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*PROJETO FINAL - CONTROLE DE AQUECIMENTO DA ÁGUA POR PWM E MONITORACAO DE TEMPERATURA */
//ALUNA: SYLVIELLY S. SOUSA
//MATRICULA: 20162045070410            PROF.: FÁBIO TIMBÓ

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, CPUDIV1,                            //habilitacao dos fusiveis
                                                      //hs = high speed (alta velocidade do oscilador > 3MHz)
                                                      //CPUDIV1 = define a divisao do clock
                                                      
#device adc = 10                                      //resolucao conversor A/D                
                                                     

#use delay(clock=20000000)     //frequencia de operacao

#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)          //habilitacao comunicacao serial
                                                      //baud = banda 
                                                      //xmit = pino de transmissão
                                                      //rcv = pino de recepcao
//inicio configuracao LCD
//#use standart_io(D)           //comentar linha caso biblioteca do lcd seja diferente

#define use_portD_lcd TRUE    //comentar linha caso biblioteca do lcd seja diferente
#define LCD_TYPE 2            //tipo lcd
#include<LCD.c>
//fim configuracao LCD

float LM_35;                  //variavel sensor de temperatura
unsigned int32 AD0;           //variavel porta analogica

//inicio programa 
void main(){

               lcd_init();           //inicializacao LCD
               lcd_gotoxy(1,1);     //posicao da palavra no LCD

               printf(lcd_putc,"SENSOR_TEMPERATURA");       //imprime palavra no LCD

               lcd_gotoxy(1,2);     //posicao da palavra no LCD

               printf(lcd_putc,"LM35");   //imprime palavra no LCD  
               delay_ms(100);             

setup_adc_ports(an0);
setup_adc(adc_clock_internal);
set_adc_channel(0);

while(TRUE){
               LM_35 = read_adc();        //lê valor de temperatura
               delay_ms(10);              //tempo de leitura
               AD0 = LM_35*0.488758;      //igual a (5/1023)*100
               
               lcd_gotoxy(1,1);     //posicao da palavra no LCD
               
               printf(lcd_putc,"\f TEMPERATURA");       //imprime palavra no LCD
               
               lcd_gotoxy(1,2);     //posicao da palavra no LCD
               printf(lcd_putc,"       %u %cC",AD0,0xDF);       //imprime palavra no LCD
               delay_ms(1000);
               
}
}
