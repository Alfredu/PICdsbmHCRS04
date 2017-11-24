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
volatile int need_to_read=1;
volatile int is_pulse;


void _ISR _INT0Interrupt(void){
    
    TMR1 = 0;
    T1CONbits.TCKPS = 2;
    T1CONbits.TON = 1;
    INTCON2bits.INT0EP = 1;
}


void __attribute__((auto_psv)) _ISR _T1Interrupt(void){
    if(is_pulse){
        LATAbits.LATA0 = 0;
        is_pulse = 0;
        T1CONbits.TON = 0;
        need_to_read = 1;
    }
}
void initPic(){
    TRISX_AS_OUTPUT = 0;
    TRISX_AS_INPUT = 1;
    AD1CON1bits.ADON = 0;
    AD1PCFGbits.PCFG0 = 1;
    AD1PCFGbits.PCFG1 = 1;
    TRISBbits.TRISB7 = 1;
    
}
int main(void) {
    initPic();
    send_pulse();
    is_pulse = 1;
    while(1){
        if(need_to_read){
            INTCON2bits.INT0EP = 0;
            IEC0bits.INT0IE = 1;
        }
    }
    return 0;
}
