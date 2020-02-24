
#include<p18f4550.h>                                                // Include Header for PIC18f455          
  
       /* ******COMPILER DIRECTIVES FOR CHIP CONFIGURATION BITS ***   */
#pragma config PLLDIV = 5 , CPUDIV = OSC1_PLL2 , USBDIV = 2    // You can write this way
// OR
#pragma config FOSC = INTOSCIO_EC
#pragma config FCMEN = OFF                                 // OR this way
#pragma config BORV = 3
#pragma config WDT = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF

/*  ***************  TIMER *************** */
       void delayzz(void)
        {              int i, j;
                        for(i=0;i<5000;i++)
                {
                          for(j=0;j<2;j++)
                      {           /* Well its Just a Timer */            }    }   }
                           


                /* ****************** MAIN ****************** */

      void main(void)
         {
                        TRISB = 0 ;                  // PORT B Setting: Set all the pins in port B to Output.
     
           while(1)  
                            {
                                LATBbits.LATB0 = 1;   // RB-1 to High  
                                LATBbits.LATB1 = 1;   // RB-1 to High

                                 delayzz();

                                LATBbits.LATB0 = 0;    // RB-0 to LOW
                                LATBbits.LATB1 = 0;    // RB-0 to LOW

                                 delayzz();


                              }
        }

/* THE END */