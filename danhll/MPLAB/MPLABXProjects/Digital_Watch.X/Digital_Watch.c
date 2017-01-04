/* 
 * File:   Digital_Watch.c
 * Author: Admin
 *
 * Created on March 9, 2013, 6:35 PM
 */
#define _LIB_BUILD

#include <stdio.h>
#include <stdlib.h>
#include <pic.h>
#include <htc.h>
#include <pic16f874a.h>
#include "lcd.h"

__CONFIG(WDTE_OFF & CPD_ON & CP_ON & FOSC_LP);

#define _XTAL_FREQ  32768     // External crystal 32.768KH
#define TICK_DELAY  1

#define SEC0             0
#define SEC1             1
#define MIN0             2
#define MIN1             3
#define HOUR0            4
#define HOUR1            5
#define MAX_DIGIT        6
#define MAX_COUPLE_DIGIT 3

#define MODE_SEC         0
#define MODE_MIN         1
#define MODE_HOUR        2
#define MODE_NORM        3

unsigned char digits[MAX_DIGIT];
unsigned char visible[MAX_DIGIT];
unsigned char mode;
/*
 * 
 */
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
    TMR0IE = 1; // Enable TMR0 interrupt
    T0CS = 0; // internal clock
    T0SE = 1; // high to low trigger
    PSA = 0; // Prescaler assign to TIMER 0
//  PS2 = 1;  // PS2:PS0 ->100 -> 1:32, 32.768KH -> 1s interrupt
//  PS1 = 0;
//  PS0 = 0;

    // For running in Proteus only
    PS2 = 1;  // PS2:PS0 ->100 -> 1:128, 32.768KH -> 1s interrupt
    PS1 = 1;
    PS0 = 1;


    PEIE = 0; // Enable unmasked pheripheral interrupts
    GIE = 1;  // Global interrupt enabled

    TRISC = 0b00000000;
    TRISD = 0b11000000;

    PORTC = 0b01111111;

    digits[0] = digits[1] = digits[2] = digits[3] = digits[4] = digits[5] = 0;
    mode = MODE_NORM;
    visible[0] = visible[1] = visible[2] = visible[3] = visible[4] = visible[5] = 1;

    // Initialize LCD
    lcd_init();
}
void OutDigit(unsigned char digit, unsigned char num)
{
    TRISD = 0b11111111;
    if(visible[digit] == 0)
    {
        return;
    }
    switch(num)
    {
        case 0:
            PORTC = 0b00111111;
            break;
        case 1:
            PORTC = 0b00000110;
            break;
        case 2:
            PORTC = 0b01011011;
            break;
        case 3:
            PORTC = 0b01001111;
            break;
        case 4:
            PORTC = 0b01100110;
            break;
        case 5:
            PORTC = 0b01101101;
            break;
        case 6:
            PORTC = 0b01111101;
            break;
        case 7:
            PORTC = 0b00000111;
            break;
        case 8:
            PORTC = 0b01111111;
            break;
        case 9:
            PORTC = 0b01101111;
            break;
    }
   switch(digit)
    {
        case SEC0:
            PORTD = 0b1111110;
            TRISD = 0b11111110;
            break;
        case SEC1:
            PORTD = 0b1111101;
            TRISD = 0b11111101;
            break;
        case MIN0:
            PORTD = 0b1111011;
            TRISD = 0b11111011;
            break;
        case MIN1:
            PORTD = 0b1110111;
            TRISD = 0b11110111;
            break;
        case HOUR0:
            PORTD = 0b1101111;
            TRISD = 0b11101111;
            break;
        case HOUR1:
            PORTD = 0b1011111;
            TRISD = 0b11011111;
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
void CalculateTime()
{
    // seconds
    if(mode == MODE_SEC)
    {
        return;
    }
    digits[0]++;
    if(digits[0] == 10)
    {
        digits[0] = 0;
        digits[1]++;
        if(digits[1] == 6)
        {
            digits[1] = 0;
            if(mode == MODE_MIN)
            {
                return;
            }
            // minutes
            digits[2]++;
            if(digits[2] == 10)
            {
                digits[2] = 0;

                digits[3]++;
                if(digits[3] == 6)
                {
                    digits[3] = 0;

                    if(mode == MODE_HOUR)
                    {
                        return;
                    }
                    // hours
                    digits[4]++;
                    if(digits[4] == 4)
                    {
                        if(digits[5] == 2)
                        {
                            digits[0] = digits[1] = digits[2] = digits[3] = digits[4] = digits[5] = 0;
                        }
                    }
                    else if(digits[4] == 10)
                    {
                        digits[4] = 0;
                        digits[5]++;
                    }
                }
            }

        }
    }
}
void main(void)
{
    Init();

    lcd_goto(0);	// select first line
    lcd_puts("~!@#$%^&*()_+=-{}[];");
    lcd_goto(0x40);	// Select second line
    lcd_puts("Hello world");

    while(1)
    {
        OutputAllDigits();
        //__delay_ms(TICK_DELAY);
    }

}
static void interrupt Interrupt_Handler(void)
{
    if(TMR0IF == 1)
    {
        CalculateTime();
        if(mode == MODE_SEC)
        {
            if(visible[0] == 0)
            {
                visible[0] = visible[1] = 1;
            }
            else
            {
                visible[0] = visible[1] = 0;
            }
        }
        else
        {
            visible[0] = visible[1] = 1;

            if(mode == MODE_MIN)
            {
                if(visible[2] == 0)
                {
                    visible[2] = visible[3] = 1;
                }
                else
                {
                    visible[2] = visible[3] = 0;
                }
            }
            else
            {
                visible[2] = visible[3] = 1;

                if(mode == MODE_HOUR)
                {
                    if(visible[4] == 0)
                    {
                        visible[4] = visible[5] = 1;
                    }
                    else
                    {
                        visible[4] = visible[5] = 0;
                    }
                }
                else
                {
                    visible[4] = visible[5] = 1;
                }

            }
        }

        TMR0IF = 0;
    }
    
    if(RBIF == 1) // RB7:RB4 changed state
    {
        if(RB4 == 0)
        {
            mode++;
            if(mode > MAX_COUPLE_DIGIT)
            {
                mode = 0;
            }
        }
        else
        {
            if(mode == MODE_NORM)
            {
                RBIF = 0;
                return;
            }
            if(RB5 == 0)  // press '-'
            {
                switch(mode)
                {
                    case MODE_SEC:
                        if(digits[0] == 0)
                        {
                            digits[0] = 9;

                            if(digits[1] == 0)
                            {
                                digits[1] = 5;
                            }
                            else
                            {
                                digits[1]--;
                            }
                        }
                        else
                        {
                            digits[0]--;
                        }
                        break;
                    case MODE_MIN:
                        if(digits[2] == 0)
                        {
                            digits[2] = 9;

                            if(digits[3] == 0)
                            {
                                digits[3] = 5;
                            }
                            else
                            {
                                digits[3]--;
                            }
                        }
                        else
                        {
                            digits[2]--;
                        }
                        break;
                    case MODE_HOUR:
                        if(digits[4] == 0)
                        {
                            if(digits[5] == 0)
                            {
                                digits[4] = 3;
                                digits[5] = 2;
                            }
                            else
                            {
                                digits[4] = 9;
                                digits[5]--;
                            }
                        }
                        else
                        {
                            digits[4]--;
                        }
                        break;
                }
            }
            else if(RB6 == 0)  // press '+'
            {
                switch(mode)
                {
                    case MODE_SEC:
                        if(digits[0] == 9)
                        {
                            digits[0] = 0;

                            if(digits[1] == 5)
                            {
                                digits[1] = 0;
                            }
                            else
                            {
                                digits[1]++;
                            }
                        }
                        else
                        {
                            digits[0]++;
                        }
                        break;
                    case MODE_MIN:
                        if(digits[2] == 9)
                        {
                            digits[2] = 0;

                            if(digits[3] == 5)
                            {
                                digits[3] = 0;
                            }
                            else
                            {
                                digits[3]++;
                            }
                        }
                        else
                        {
                            digits[2]++;
                        }
                        break;
                    case MODE_HOUR:
                        if(digits[4] == 3)
                        {
                            if(digits[5] == 2)
                            {
                                digits[4] = 0;
                                digits[5] = 0;
                            }
                            else
                            {
                                digits[4]++;
                            }
                        }
                        else if(digits[4] == 9)
                        {
                            digits[4] = 0;
                            digits[5]++;
                        }
                        else
                        {
                            digits[4]++;
                        }
                        break;
                }
            }
        }
        RBIF = 0;
    }
}


