/*
 * File:   main.c
 * Author: Alfredu
 *
 * Created on 22 November 2017, 11:57
 */
#include <xc.h>
#define _XTAL_FREQ 8000000
#define FCY        500000UL
#include <libpic30.h>
#include "HCSR04.h"
#include "pins.h"
#define TRISX_AS_OUTPUT TRISBbits.TRISB2
#define TRISX_AS_INPUT TRISBbits.TRISB7
#define TRIGGER_PIN LATBbits.LATB2
#define ECHO_PIN LATBbits.LATB7

#pragma config FNOSC = FRC


void _ISR _INT0Interrupt(void){
    TMR1 = 0;
        T1CONbits.TCKPS = 2;
        T1CONbits.TON = 1;
        INTCON2bits.INT0EP = 1;
}




void initPic(){
    TRISX_AS_OUTPUT = 0;
    TRISX_AS_INPUT = 1;
    
}
int delay_abulto(int cosa){
    
    TMR1 = 0;
    if(cosa==0){
        PR1 = 5000;
        T1CONbits.TCKPS = 0;
    }
    else{
        PR1 = 65535;
        T1CONbits.TCKPS = 3;
    }
        
    T1CONbits.TON = 0;
    
    T1CONbits.TCS = 0; //Internal
    
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;
    
    IFS0bits.T1IF = 0;
    while(!IFS0bits.T1IF);
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 0;
    return 0;
}
int main(void) {
    initPic();
    while(1){
        TRIGGER_PIN = 1;
        delay_abulto(0);
        INTCON2bits.INT0EP = 1;
        IEC0bits.INT0IE = 1;
        TRIGGER_PIN = 0;
        delay_abulto(75);
    }
    return 0;
}
