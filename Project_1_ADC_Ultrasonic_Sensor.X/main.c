/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif
#include <stdio.h>
#include <stdlib.h>
//#include <proc/p32mx460f512l.h>
#include <sys/attribs.h>
/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
unsigned int ADCValue = 1000;
int test_var = 1;
/* i.e. uint32_t <variable_name>; */
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/



void SimpleCounterDelay(int CountLimit){
    int x;
    for (x = 0; x < CountLimit; x++){
    }  
}

int32_t main(void)
{
    TRISBSET = 1 << 2;
    AD1PCFG = 0xFFFB; // PORTB = Digital; RB2 = analog
    AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling
                      // and starts converting
    AD1CHS = 0x00020000; // Connect RB2/AN2 as CH0 input
    
    AD1CSSL = 0; 
    AD1CON3 = 0x0002; // Manual Sample, TAD = internal 6 TPB
    AD1CON2 = 0;
    
    AD1CON1SET = 0x8000; // turn on ADC
    while(1)            // repeat continuously
    {
        AD1CON1SET = 0x0002; //start sampling
        SimpleCounterDelay(1000); //Simple Delay, later add a time based delay
        AD1CON1CLR = 0x0002; //Start Converting;
        while (!(AD1CON1 & 0x0001)) {}; //Wait until conversion is done
        ADCValue = ADC1BUF0; //write ADC value to parameter.
        test_var = test_var+1;
    }  
}

