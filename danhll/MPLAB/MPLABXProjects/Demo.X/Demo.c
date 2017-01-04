/* 
 * File:   Demo.c
 * Author: Admin
 *
 * Created on March 20, 2013, 9:28 PM
 */
#define _LIB_BUILD
#include <stdio.h>
#include <stdlib.h>
#include <htc.h>
#include <pic.h>
#include <pic16f874a.h>

__CONFIG (CP_OFF & WDTE_OFF & PWRTE_ON & FOSC_HS & WRT_OFF & LVP_OFF & CPD_OFF);

//#define _XTAL_FREQ  32768     // External crystal 32.768KH
#define _XTAL_FREQ  20000000     // External crystal 20MH

void Init(void)
{
    // All RAx are digital ports
    PCFG0 = 0;
    PCFG1 = 1;
    PCFG2 = 1;
    PCFG3 = 0;
}
void main(void)
{
    Init();

    TRISC = 0b00000000;
    PORTC = 0b00000000;
    TRISD = 0b00000000;
    PORTD = 0b11111111;

    while(1)
    {
        
    }
}

