/*
 * File:   RGB_C.c
 * Author: Admin
 *
 * Created on April 20, 2016, 8:28 AM
 */

// ********************************************************************************
// Pinout connections 
//                            ___ ___
//                       Vdd -|1 ^ 8|- Vss
//      Sequence Change Sw1  -|2   7|- red output
//              blue output  -|3   6|- green output
//  MCLR. tie to Vdd via 1K  -|4   5|- not used
//                           ¯¯¯¯¯¯¯
//  Ensure that MCLR is pulled to Vdd using 1K resistor for 12F629/675.
        
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = EXTRCIO   // Oscillator Selection bits (RC oscillator: I/O function on GP4/OSC2/CLKOUT pin, RC on GP5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = ON          // Code Protection bit (Program Memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)

#include "upic12f629.h"



#define _XTAL_FREQ 4000000

#define PIN_R       GPIO0
#define PIN_G       GPIO1
#define PIN_B       GPIO4
#define PIN_SW      GPIO2
#define TRISIO_R    TRISIO0
#define TRISIO_G    TRISIO1
#define TRISIO_B    TRISIO4
#define TRISIO_SW   TRISIO2

rgb_t rgb[IND_GRB_MAX];

inline void udelay_rel(unsigned char count)
{
    for(unsigned char i = 0; i < count; i++)
        for(unsigned char j = 0; j < 10; j++);
}

inline void pwm1(rgb_t *x) 
{ 
    udelay_rel(x->duration);
    switch(x->pin) 
    { 
    case IND_R: 
        USET2(PIN_R, OFF); 
        break; 
    case IND_G: 
        USET2(PIN_G, OFF); 
        break; 
    case IND_B: 
        USET2(PIN_B, OFF); 
        break; 
    } 
}

inline void pwm2() 
{ 
    USET2(PIN_R, ON); 
    USET2(PIN_G, ON); 
    USET2(PIN_B, ON); 
//    pwm1(&rgb[0]); 
//    pwm1(&rgb[1]); 
//    pwm1(&rgb[2]); 
//    udelay_rel(255 - rgb[2].duration);
//    __delay_us(0);
//    USET2(PIN_B, OFF); 
//    USET2(PIN_G, OFF); 
//    __delay_us(2000);
//    USET2(PIN_R, OFF); 
//    __delay_us(550);
    for(unsigned char i = 0; i < 256; i++)
    {
        if(i == rgb[0].duration)
            USET2(PIN_R, OFF); 

        if(i == rgb[1].duration)
            USET2(PIN_G, OFF); 

        if(i == rgb[2].duration)
            USET2(PIN_B, OFF); 
    }
}


void main(void) 
{
    GPIO = 0x00;
    TRISIO = ~(1<<0 | 1<<1 | 1<<4 );
    // Load OSCCAL value
    OSCCAL = __osccal_val();
    
    
    // Set pin 7(R), 6(G), 3(B) as Output
    UOUTPUT_PORT(TRISIO_R);
    UOUTPUT_PORT(TRISIO_G);
    UOUTPUT_PORT(TRISIO_B);

    // Set pin2(SW) as input
    UINPUT_PORT(TRISIO_SW);
    
    // Set IOC on pin2
    // Test
    rgb[0].duration = 200;//50
    rgb[0].pin = IND_B;
    
    rgb[1].duration = 200;//100
    rgb[1].pin = IND_G;

    rgb[2].duration = 200;//200
    rgb[2].pin = IND_R;
    
    while(1)
    { 
//        USET2(PIN_R, ON); 
        pwm2();
    }
//    while(1)
//    { 
//    USET2(PIN_R, ON);
//    __delay_ms(1000);
//    USET2(PIN_R, OFF);
//    USET2(PIN_G, ON);
//    __delay_ms(1000);
//    USET2(PIN_G, OFF);
//    USET2(PIN_B, ON);
//    __delay_ms(1000);
//    USET2(PIN_B, OFF);
//    }
}
