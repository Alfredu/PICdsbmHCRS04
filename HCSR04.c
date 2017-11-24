/*
 * File:   HCSR04.c
 * Author: Alfredu
 *
 * Created on 22 November 2017, 12:25
 */


#include "xc.h"
#include "pins.h" 

void send_pulse(){
    //Apagar timer
    TRIGGER_PIN = 0;
    T1CONbits.TON = 0;
    T1CONbits.TCKPS = 0;
    T1CONbits.TCS = 0; //Internal
    T1CONbits.TGATE = 0;
    TMR1 = 0;
    PR1 = 80;
    IEC0bits.T1IE = 1;
    TRIGGER_PIN = 1;
    T1CONbits.TON = 1;
}

