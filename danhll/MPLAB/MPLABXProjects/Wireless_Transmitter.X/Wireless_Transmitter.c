/* 
 * File:   Wireless_Transmitter.c
 * Author: Admin
 *
 * Created on April 26, 2013, 11:38 AM
 */

#define _LIB_BUILD

#include <stdio.h>
#include <stdlib.h>
#include <pic.h>
#include <htc.h>
#include <pic12f629.h>

__CONFIG (CP_ON & CPD_ON & MCLRE_OFF & WDTE_OFF & FOSC_INTRCIO);

#define _XTAL_FREQ  4000000     // Internal 4MH

#define STROPE() {GP5 = 0; __delay_ms(2000); GP5 = 1;};
/*
 * 
 */
void Init(void)
{
    CM0 = CM1 = CM2 = 1;
    CMIE = 0;
    ADIE = 0;
    TRISIO = 0b001000;
    GPIO = 0b111111;
    GPIE = 1;
    IOC3 = 1;
    GIE = 1;
}
void main(void)
{
    Init();
    while(1)
    {
    }
}

static void interrupt Interrupt_Handler(void)
{
    if(GPIF == 1)
    {
        if(GP3 == 0)
        {
            STROPE();
        }
        GPIF = 0;
    }

}