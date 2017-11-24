/*
 * File:   main.c
 * Author: Alfredu
 *
 * Created on 22 November 2017, 11:57
 */
#include <xc.h>
#include "HCSR04.h"
#include "pins.h"
#define _XTAL_FREQ 8000000
#define TRISX_AS_OUTPUT TRISAbits.TRISA0
#define TRISX_AS_INPUT TRISAbits.TRISA1
#pragma config FNOSC = FRC
volatile int need_to_pulse;
void __attribute__((auto_psv)) _ISR _T1Interrupt(void){
    
}
void initPic(){
    TRISX_AS_OUTPUT = 0;
    TRISX_AS_INPUT = 1;
    AD1CON1bits.ADON = 0;
    AD1PCFGbits.PCFG0 = 1;
    AD1PCFGbits.PCFG1 = 1;
}
int main(void) {
    initPic();
    while(1){
        
    }
    return 0;
}
