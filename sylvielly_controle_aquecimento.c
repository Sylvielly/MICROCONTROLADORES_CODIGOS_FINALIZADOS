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
#define LCD_TYPE 2               //tipo lcd
#include "LCD8B.c"               //hiperlink programa LCD
#include "12Keys.c"              //hiperlink programa teclado matricial
//#include<LCD.c>
//fim configuracao LCD

//declaracao de variaveis
long int LM_35;                  //variavel sensor de temperatura
long int AD3;                    //variavel porta analogica (variavel longa de 32bits - int32 [%ld])
int vetor[2],valor_config=0;
int auxiliar = 0, n=0, n2=0;
int conta=0;
#int_timer0
void tempo(){
set_timer0(131+get_timer0());
n++;
n2++;
}

//inicio programa 
void main(){
setup_timer_0(RTCC_DIV_64|RTCC_INTERNAL|RTCC_8_BIT);
set_timer0(131);
enable_interrupts(GLOBAL);
enable_interrupts(INT_TIMER0);

               port_b_pullups(True);          //habilitacao de pullups (para o teclado matricial)
               lcd_ini();                    //inicializacao LCD para a biblioteca em questao
               setup_timer_2(T2_DIV_BY_4,249,1);
               
               
               
setup_adc_ports(AN0_TO_AN3);                        //pino AN3 sera o pino onde o LM35 ficara (pino 2 do LM35)
setup_adc(adc_clock_internal);
set_adc_channel(3);                                //seta canal analógico 3          

               tecla_pres=0;                 //verifica condicao de tecla pressionada
               int valor=100;                //valor para ajuste duty cycle PWM             
               lcd_pos_xy(1,1);              //seleciona posicao no LCD 
               printf(lcd_escreve,"\fTEMP. DESEJADA");      //solicita ao usuario valor desejado de temperatura no LCD
               printf("\r\nDIGITE TEMPERATURA DESEJADA NO TECLADO MATRICIAL\r\n");           //solicita ao usuario valor desejado de temperatura na serial     
//inicio while
while(TRUE){
               //para o projeto, usuario digita valor de temperatura no teclado
               //inicio teclado matricial
               //analise do teclado matricial de forma que ele capture o valor digitado pelo usuario
              if(conta<=1){                                          //testa tecla digitada
               tecla = trata_teclas();
               
               if (tecla_pres)      
               {
                              lcd_pos_xy((conta+1),2);               //coloca posicao do primeiro caractere do teclado
                              printf(lcd_escreve,"%c", tecla);
                              printf("%c",tecla);                    //captura caractere digitado
                                 
                              vetor[conta] = tecla-48;               //converte o caractere capturado do teclado em decimal
                             
                              conta++;                               //incrementa posicao enquanto  
                } 
                tecla_pres = 0;           //tecla pressionada volta para zero depois de serem capturados os dois digitos
                }
               //fim teclado matricial
               
               //inicio PWM
               else if(conta>=2){                              //quando o segundo digito for capturado, configura temperatura
                         
                        valor_config = vetor[0]*10+vetor[1];   //valor configurado pelo usuario de temperatura utilizando vetor
                        LM_35 = read_adc();                    //LM35 lê valor de temperatura real no resistor de aquecimento
                        delay_ms(10);        
                        AD3 = LM_35*0.488758;                  //converte valor lido em temperatura
                       
                     if((valor_config <= AD3))                 //compara se valor configurado é igual ao valor real lido pelo sensor
                        {     
                              set_pwm2_duty(0);                //seta PWM para zero  caso temperatura seja igual ao valor setado pelo usuario
                              setup_ccp2(CCP_PWM);             //envia para o pino CCP2 o duty cycle do PWM
                        if(n2==50){                            //tempo para escrever na tela do LCD
                              lcd_pos_xy(1,1);
                              printf(lcd_escreve,"\fAJUSTE OK!!!");      //temperatura ajustada        
                              lcd_pos_xy(1,2);
                              printf(lcd_escreve,"TEMP CONF = %d",valor_config);
                              n2=0;
                        }
                              if(n==2500)                      //tempo para escrever na serial
                              {
                                 printf("\r\nAJUSTE OK!!!");
                                 printf("\r\nTEMPERATURA CONFIGURADA = %d",valor_config);
                                 n=0;
                                 delay_ms(1000);
                              }
                              
                              
                              
                        }
                        else{   //mostra temperatura em tempo real no LCD e serial
                              auxiliar = AD3;
                              if(n2==50){       
                              lcd_pos_xy(1,1);
                              printf(lcd_escreve,"\fTEMP REAL = %lu",AD3);       //escreve no LCD valor em tempo real
                              lcd_pos_xy(1,2);
                              printf(lcd_escreve,"TEMP CONF = %d",valor_config); //exibe no LCD valor configurado
                              n2=0;}
                              if(n==2500)                      //tempo para escrever na serial
                              {  
                                
                                 printf("\r\nTEMPERATURA REAL = %lu",AD3);                      //exibe na tela (a partir da serial) valor em tempo real
                                 printf("\r\nTEMPERATURA CONFIGURADA = %d",valor_config);       //exibe na tela (a partir da serial) valor configurado
                                 n=0;
                              }
                              
                              set_pwm2_duty(valor);              //seta PWM para zero  caso temperatura seja igual ao valor setado pelo usuario    
                              setup_ccp2(CCP_PWM);               //envia para o pino CCP2 o duty cycle do PWM
                            }
                        
                    }
                    
             } //fim while
             
} //fim programa
