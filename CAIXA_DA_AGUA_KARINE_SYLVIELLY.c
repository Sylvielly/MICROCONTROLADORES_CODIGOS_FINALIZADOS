/*MICROCONTROLADORES - S6 ENGENHARIA DE CONTROLE E AUTOMACAO*/
/*ATIVIDADE DE CLASSE 10/06/2019 - CAIXA D'AGUA COM CISTERNA EM C*/
//ALUNA: SYLVIELLY S. SOUSA / KARINE MENDES

#include <18F4550.h>
#fuses hs, nowdt, CPUDIV1, NOMCLR, noprotect, nolvp //habilitacao dos fusiveis
                                                    //hs = high speed (alta velocidade do oscilador > 3MHz)
                                                    //noprotect = codigo nao protegido (direitos autorais)
                                                   //NOMCLR = desabilita master clear (nao energiza pino 1 MCLR) 
                                                   //nolvp = desabilita low voltage pin
                                                  //nowtd = desabilita watchdog
 
#use   delay(clock=20000000)

//DEFINICOES DE PINOS PARA CAIXA D'AGUA E CISTERNA
#define sensor_baixo       pin_b0
#define sensor_alto        pin_b1
#define estado_cisterna    pin_b2 
#define bomba              pin_d0

int aciona_bomba;
int alto;
int baixo;
int cisterna;


//INICIO LOGICA DE ACIONAMENTO
aciona_bomba (alto,baixo,cisterna) 
{

if(cisterna==1)                        //se a cisterna for == 1 [cheia], liga bomba
   {
      if ((alto==0)&&(baixo==0))       //verificacao dos sensores da cx dagua se esta seca, se sim liga a bomba
      {return 1;}
   
      if ((alto==1)&&(baixo==1))       //verificacao dos sensores da cx dagua se esta cheia, se sim desliga bomba
      {return 0;}
   }
else
   {return 0;}                         //se cisterna for == 0, a bomba nao pode ser ligada (condicao de seguranca)
}
//FIM LOGICA DE ACIONAMENTO

//INICIO PROGRAMA PRINCIPAL
void main()
{
   
   int estado=0;                      //estado bomba
   int x,y,z; 

while(true)
{
   if (input(sensor_alto)==1)       //estado sensor alto 
         {x=1;}
   else 
         {x=0;}
   
   if (input(sensor_baixo)==1)      //estado sensor baixo
         {y=1;} 
   else 
         {y=0;}
   if(input(estado_cisterna)==1)    //estado cisterna
         {z=1;}
   else
         {z=0;}

estado = aciona_bomba(x,y,z);
output_bit(bomba,estado);

}
//INICIO PROGRAMA PRINCIPAL
}
