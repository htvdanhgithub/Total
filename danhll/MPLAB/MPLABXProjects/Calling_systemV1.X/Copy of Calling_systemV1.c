/* 
 * File:   Calling_systemV1.c
 * Author: Admin
 *
 * Created on April 3, 2013, 9:44 PM
 */

#define _LIB_BUILD

#include <stdio.h>
#include <stdlib.h>
#include <pic.h>
#include <htc.h>
#include <pic16f628a.h>

__CONFIG (CP_ON & WDTE_OFF & PWRTE_ON & FOSC_INTOSCIO & MCLRE_ON & LVP_OFF & CPD_ON);

#define _XTAL_FREQ  4000000     // Internal 4MH

#define MAX_NUM 5
#define MODE_NORMAL 0
#define MODE_REVIEW 1
#define TICK_PER_SECOND 50
#define TIMEOUT_IN_SECOND 60


unsigned char unit[MAX_NUM] = {0, 0, 0, 0, 0};
unsigned char ten[MAX_NUM] = {0, 0, 0, 0, 0};
unsigned char timeout = 0;

unsigned char curNorIndex = 0;
unsigned char curReviewIndex = 0;
unsigned char numNorCount = 0;
unsigned char numReviewCount = 0;
unsigned char curTick = 0;
unsigned char mode = MODE_REVIEW;
void Init(void)
{
    // 4 MH internal clock
    OSCF = 1;

    // Disable Timer 0
    T0IE = 0;

    T1OSCEN = 0;
    
    // Voltage reference
    VREN = 0;

    // Disable CM
    CMIE = 0;
    // R0-R7: output
    TRISA = 0b00100000;
    // RB6, RB7 output
    TRISB = 0b00111111;

    // Pull-up RBx
    nRBPU = 0;

    // Interrupt on change RBx
    RBIE = 1;

    // Peripheral unmasked interrupts
    PEIE = 1;

    // Global interrupt
    GIE = 1;
}
unsigned char tmp;
#define load_led_data(a, b) do{PORTB &= 0b00111111; PORTA = a; tmp = PORTB; if(b == 0){tmp |= 0b01000000; tmp &= 0b01111111;}else{tmp |= 0b10000000; tmp &= 0b10111111;} PORTB = tmp;}while(0)
void Display(unsigned char num, unsigned char pos)
{
    switch(num)
    {
        case 0:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b10100000;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b10100000;
                RB7 = 1;

            }
            break;
        case 1:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b11111001;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b11111001;
                RB7 = 1;

            }
            break;
        case 2:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b01100100;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b01100100;
                RB7 = 1;

            }
            break;
        case 3:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b01110000;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b01110000;
                RB7 = 1;

            }
            break;
        case 4:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00111001;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00111001;
                RB7 = 1;

            }
            break;
        case 5:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00110010;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00110010;
                RB7 = 1;

            }
            break;
        case 6:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00100010;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00100010;
                RB7 = 1;

            }
            break;
        case 7:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b11111000;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b11111000;
                RB7 = 1;

            }
            break;
        case 8:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00100000;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00100000;
                RB7 = 1;

            }
            break;
        case 9:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00110000;
                RB6 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00110000;
                RB7 = 1;

            }
            break;
    }
}
void InsertNewIndex(unsigned char num)
{
    timeout = TIMEOUT_IN_SECOND;
    unsigned char t_unit = num%10;
    unsigned char t_ten = num/10;

    for(unsigned char i = 0; i < numNorCount; i++)
    {
        if(t_unit != unit[i])
        {
            continue;
        }
        if(t_ten != ten[i])
        {
            continue;
        }

        return;
    }
    if(curNorIndex == MAX_NUM)
    {
        curNorIndex = 0;
    }

    unit[curNorIndex] = t_unit;
    ten[curNorIndex] = t_ten;
    numNorCount++;
    if(numNorCount > MAX_NUM)
    {
        numNorCount = MAX_NUM;
    }

    curNorIndex++;
}
unsigned char GetNextIndex(unsigned char index)
{
    if(index == numNorCount - 1)
    {
        return 0;
    }
    else
    {
        return index + 1;
    }
}
void DisplayIndex(unsigned char index)
{
    curTick++;
    if(curTick == TICK_PER_SECOND)
    {
        curTick = 0;
        if(timeout == 0)
        {
            for(unsigned char i = 0; i < MAX_NUM; i++)
            {
                unit[i] = ten[i] = 0;
            }

            curNorIndex = 0;
            curReviewIndex = 0;
            numNorCount = 0;
            numReviewCount = 0;
            mode = MODE_NORMAL;
        }
        else
        {
            timeout--;
        }

        if(mode == MODE_REVIEW)
        {
            curReviewIndex = GetNextIndex(curReviewIndex);

            numReviewCount++;
        }
    }

    Display(unit[index], 0);
    __delay_ms(10);
    Display(ten[index], 1);
    __delay_ms(10);
    
    if(mode == MODE_REVIEW)
    {
        if(numReviewCount == numNorCount)
        {
//            mode = MODE_NORMAL;
        }

    }
}
void main(void)
{
    Init();

    while(1)
    {
        if(mode == MODE_NORMAL)
        {
            DisplayIndex(curNorIndex - 1);
        }
        else
        {
            DisplayIndex(curReviewIndex);
        }
    }
    //DisplayIndex(0);
//    while(1)
//    {
//    Display(unit[0], 1);
//    TRISA = 0b00100000;
//    PORTA = 0b00000000;
    // RB6, RB7 output
//    TRISB = 0b00111111;
//    PORTB = 0b11000000;
//    Display(ten[0], 0);

//    }
//    load_led_data(0b0111111, 1);
/*    TRISA = 0b00000000;
    PORTA = 0b00000000;
    TRISB &= 0b00111111;
    RB6 = RB7 = 1;*/
}
static void interrupt Interrupt_Handler(void)
{
    if(RBIF == 1) // RB7:RB4 changed state
    {
        if(RB4 == 0)
        {
            InsertNewIndex(PORTB & 0b00001111);
        }
        else if(RB5 == 0)
        {
            mode = MODE_REVIEW;

            if(curNorIndex == numNorCount)
            {
                curReviewIndex = 0;
            }
            else
            {
                curReviewIndex = curNorIndex;

            }
            numReviewCount = 0;
        }
        RBIF = 0;
    }

}
