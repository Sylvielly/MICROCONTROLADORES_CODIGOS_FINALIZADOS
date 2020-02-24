/*MICROCONTROLADORES - ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*PROJETO FINAL - CONTROLE DE AQUECIMENTO DA ÁGUA POR PWM E MONITORACAO DE TEMPERATURA COM LM35*/
//ALUNA: SYLVIELLY S. SOUSA
//MATRICULA: 20162045070410            PROF.: FÁBIO TIMBÓ

#include<18f4550.h>           //PIC18F4550
#fuses hs, nowdt, CPUDIV1,brownout,nolvp                            //habilitacao dos fusiveis
                                                                    //hs = high speed (alta velocidade do oscilador > 3MHz)
                                                                    //CPUDIV1 = define a divisao do clock               
                                                     
#device adc = 10                                      //resolucao conversor A/D    

#use delay(clock=8000000)     //frequencia de operacao

#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)          //habilitacao comunicacao serial
                                                      //baud = banda 
                                                      //xmit = pino de transmissão
                                                      //rcv = pino de recepcao


//trocar AN0 por AN3
//inicio configuracao LCD
//#use standart_io(B)           //comentar linha caso biblioteca do lcd seja diferente

//#define use_portD_lcd TRUE     //comentar linha caso biblioteca do lcd seja diferente
//#define LCD_TYPE 2               //tipo lcd
//#include "LCD8B.c"               //hiperlink programa LCD
//#include "12Keys.c"              //hiperlink programa teclado matricial
//#include<LCD.c>
//fim configuracao LCD

//declaracao de variaveis
long int LM_35;                  //variavel sensor de temperatura
unsigned int32 AD3;              //variavel porta analogica (variavel longa de 32bits - int32 [%ld])



//inicio programa 
void main(){
            
               
               
setup_adc_ports(AN0_TO_AN3);     
setup_adc(adc_clock_internal);//pino AN0 sera o pino onde o LM35 ficara (pino 2 do LM35)
set_adc_channel(3);


//inicio while
while(TRUE){

                         
                        LM_35 = read_adc();
                        delay_ms(10);
                        AD3 = LM_35;                  //valor real 
                        printf("AD3 %lu",ad3);
                       
                 
             
} 
}//fim programa
