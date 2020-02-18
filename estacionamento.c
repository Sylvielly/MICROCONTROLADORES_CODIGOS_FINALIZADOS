#include <18F4550.h>
#define led1 pin_d0
#define led2 pin_d1
#define entrada1 pin_b0
#define entrada2 pin_b1
#define saida1 pin_b2
#define saida2 pin_b3
#fuses HS,CPUDIV1,NOWDT,NOMCLR  
int vagas=0;
int estado1=1;
int estado2=1;

void main()
{
while(1)
{

if((input(entrada1)==1) && vagas<=9)
{
output_high(led1);
}
if(input(entrada2)==1)
{
estado1=0;
}
if((estado1==0) && (input(entrada2)==1))
{
delay_ms(1000);
vagas++;


output_low(led1);
estado1=1;
}
}
}
