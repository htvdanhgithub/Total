/* 
 * File:   Calling_system.c
 * Author: Admin
 *
 * Created on March 12, 2013, 8:45 PM
 */

#define _LIB_BUILD

#include <stdio.h>
#include <stdlib.h>
#include <pic.h>
#include <htc.h>
#include <pic16f874a.h>


__CONFIG(WDTE_OFF & CPD_ON & CP_ON & FOSC_HS);

#define _XTAL_FREQ  32768     // External crystal 32.768KH

#define TRIS_REMOTE_CTRL      TRISA
#define PORT_REMOTE_CTRL      PORTA
#define SET_TRIS_REMOTE_CTRL  (TRIS_REMOTE_CTRL |= 0b00001111)
#define DATA_REMOTE_CTRL      ((PORT_REMOTE_CTRL & 0b00001111) + 1)

#define SET_TRIS_BUZZER  (TRISA &= 0b11011111)
#define PORT_BUZZER  RA5

#define TRIS_LED_DATA  TRISC
#define PORT_LED_DATA  PORTC

#define TRIS_LED_SELECTOR  TRISD
#define PORT_LED_SELECTOR  PORTD

#define MAX_DIGIT        6

#define MODE_NORM        0
#define MODE_LEARNING    1

#define TICK_DELAY       1

#define BLINK_TIME       10
#define BUZZING_TIME     10
#define TIMER1_INT_COUNT_1S     9


unsigned char digits[MAX_DIGIT];
unsigned char visible[MAX_DIGIT];
unsigned char timeout[MAX_DIGIT];
unsigned char mode;
unsigned char timer1_interrupt_count;
void Init(void)
{
    // All RAx are digital ports
    PCFG0 = 0;
    PCFG1 = 1;
    PCFG2 = 1;
    PCFG3 = 0;

    // config interrupt configuration
    //TRISB = 0b11111111;
    RBIE = 1; // Enable RB port change interrupt

  // Timer 0 interrupt
/*    TMR0IE = 1; // Enable TMR0 interrupt
    T0CS = 0; // internal clock
    T0SE = 1; // high to low trigger
    PSA = 0; // Prescaler assign to TIMER 0
//  PS2 = 1;  // PS2:PS0 ->100 -> 1:32, 32.768KH -> 1s interrupt
//  PS1 = 0;
//  PS0 = 0;

    // For running in Proteus only
    PS2 = 1;  // PS2:PS0 ->100 -> 1:128, 32.768KH -> 1s interrupt
    PS1 = 1;
    PS0 = 1;*/

    // Disble timer0
    TMR0IE = 0;
    // Timer 1
    T1OSCEN = 1;
    
    T1CKPS1 = 1;
    T1CKPS0 = 1;
    TMR1CS = 0;
    TMR1ON = 1;
    
    TMR1IE = 1;


    PEIE = 0; // Enable unmasked pheripheral interrupts
    GIE = 1;  // Global interrupt enabled

    timer1_interrupt_count = 0;

    SET_TRIS_REMOTE_CTRL;

    SET_TRIS_BUZZER;
    PORT_BUZZER = 0;
    
    TRIS_LED_DATA = 0b00000000;
    TRIS_LED_SELECTOR = 0b11000000;

    PORT_LED_SELECTOR = 0b00000000;

    digits[0] = 0; digits[1] = 1; digits[2] = 2; digits[3] = 3; digits[4] = 4; digits[5] = 5;
    visible[0] = visible[1] = visible[2] = visible[3] = visible[4] = visible[5] = 0;

    mode = MODE_NORM;

}
void OutDigit(unsigned char digit, unsigned char num)
{
    if(visible[digit] == 0)
    {
        return;
    }
    switch(num)
    {
        case 0:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b11000000;
            break;
        case 1:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b11111001;
            break;
        case 2:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b10100100;
            break;
        case 3:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b10110000;
            break;
        case 4:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b10011001;
            break;
        case 5:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b10010010;
            break;
        case 6:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b10000010;
            break;
        case 7:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b11111000;
            break;
        case 8:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b10000000;
            break;
        case 9:
            PORT_LED_SELECTOR = 0b00000000;
            PORT_LED_DATA = 0b10010000;
            break;
    }
   switch(digit)
    {
        case 0:                  
            PORT_LED_SELECTOR = 0b00000001;
            break;
        case 1:
            PORT_LED_SELECTOR = 0b00000010;
            break;
        case 2:
            PORT_LED_SELECTOR = 0b00000100;
            break;
        case 3:
            PORT_LED_SELECTOR = 0b00001000;
            break;
        case 4:
            PORT_LED_SELECTOR = 0b00010000;
            break;
        case 5:
            PORT_LED_SELECTOR = 0b00100000;
            break;
    }
}
void OutputAllDigits()
{
    for(unsigned char i = 0; i < MAX_DIGIT; i++)
    {
        OutDigit(i, digits[i]);
    }

}

void main(void)
{
    Init();


    while(1)
    {
        OutputAllDigits();
//        __delay_ms(TICK_DELAY);
//        OutDigit(0, digits[0]);
    }

}

static void interrupt Interrupt_Handler(void)
{
/*    if(TMR0IF == 1)
    {
//        timer1_interrupt_count++;
//        if(timer1_interrupt_count != TIMER1_INT_COUNT_1S)
//        {
//            TMR1IF = 0;
//            return;
//        }
//        timer1_interrupt_count = 0;
        for(unsigned char i = 0; i < MAX_DIGIT; i++)
        {
            if(timeout[i] > 0)
            {
                timeout[i]--;
                if(visible[i] == 0)
                {
                    visible[i] = 1;
                }
                else
                {
                    visible[i] = 0;
                }
            }
            else
            {
                visible[i] = 1;
            }
        }

        TMR0IF = 0;
    }*/

    if(TMR1IF == 1)
    {
        TMR1IF = 0;
    }
    if(RBIF == 1) // RB7:RB4 changed state
    {
        if(RB5 == 0)
        {
            digits[5] = digits[3];
            timeout[5] = timeout[3];
            digits[4] = digits[2];
            timeout[4] = timeout[2];

            digits[3] = digits[1];
            timeout[3] = timeout[1];
            digits[2] = digits[0];
            timeout[2] = timeout[0];

            digits[0] = DATA_REMOTE_CTRL;
            if(digits[0] > 9)
            {
                digits[0] -= 10;
                digits[1] = 1;
            }
            else
            {
                digits[1] = 0;
            }

            timeout[1] = timeout[0] = BLINK_TIME;
            PORT_BUZZER = 1;
            __delay_ms(100);
            PORT_BUZZER = 0;
            __delay_ms(500);
            PORT_BUZZER = 1;
            __delay_ms(100);
            PORT_BUZZER = 0;
        }

        RBIF = 0;
    }
}
