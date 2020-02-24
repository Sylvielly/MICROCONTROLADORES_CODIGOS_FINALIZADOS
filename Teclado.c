/*******************************************************************************
*                     Kit de desenvolvimento ACEPIC PRO V2.0                   *
*                      ACEPIC Tecnologia e Treinamento LTDA                    *
*                               www.acepic.com.br                              * 
*                                                                              *
*Objetivo: Teste do teclado matricial 4 X 4                                    *
*          Envia pela serial e escreve no LCD a tecla pressionada              *
*Obs.:                                                                         *
********************************************************************************/
#include<18F4550.h> 
#use delay (clock=8000000)        
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 
#use rs232(baud=9600, xmit = PIN_C6, rcv = PIN_C7)          //serial configuracao 

int conta=0;

void main()
 {
  port_b_pullups(True);          //habilitacao de pullups
  
  lcd_ini();                     //inicializacao do LCD
    
  printf("TESTE DE FUNCIONAMENTO DO TECLADO\n\r");
  printf("=============================\n\r");
  printf("\n\rPlaca de desenvolvimento ACEPIC 40\r\n");
  printf("\n\rMicrocontrolador PIC 18F4550;\r\n");
  printf("Baudrate = 9600 BPS;\r\n");
  printf("DataBits = 8.\r\n");
  printf("\r\n");
  printf("\r\nFaz a leitura da tecla digitada no teclado\r\n");
  printf("mostrando no Display e na serial.\r\n");
  
  printf(lcd_escreve,"\f   PIC18F4550");
  printf(lcd_escreve,"\n    Teclado.");
  
  delay_ms(1000);
  
  lcd_escreve("\f");
  printf(lcd_escreve,"Digite:\n");  
  
  tecla_pres=0;
   
  while(TRUE)
              {
               tecla = trata_teclas();
               if (tecla_pres)
                              {
                              if (conta>=16) 
                                                {
                                                 conta = 0;
                                                 lcd_pos_xy(1,2);
                                                 printf(lcd_escreve,"                ");
                                                 lcd_pos_xy(1,2); 
                                                }
                              printf(Lcd_escreve,"%c", tecla);
                              printf("%c",tecla); 
                              conta++;                             
                              }
               tecla_pres = 0;           
             }
}

