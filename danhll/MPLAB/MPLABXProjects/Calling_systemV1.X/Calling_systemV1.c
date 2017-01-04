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
#define MODE_FLICKER 1
#define TICK_PER_SECOND 50
#define TIMEOUT_IN_SECOND 60
#define TIMEOUT_FLICK_IN_SECOND 3
#define TIMEOUT_FLIP_FLOP_IN_TICK 10

#define beep() {RB5 = 1; __delay_ms(30); RB5 = 0;}


unsigned char unit[MAX_NUM] = {0, 0, 0, 0, 0};
unsigned char ten[MAX_NUM] = {0, 0, 0, 0, 0};
unsigned char flick[MAX_NUM] = {0, 0, 0, 0, 0};
unsigned char timeout[MAX_NUM] = {0, 0, 0, 0, 0};
unsigned char visible[MAX_NUM] = {1, 1, 1, 1, 1};

unsigned char curNorIndex = 0;
unsigned char curViewIndex = 0;
unsigned char numNorCount = 0;
unsigned char curTick = 0, curFlipFlopTick = 0;
unsigned char mode = MODE_NORMAL;
unsigned char moved = 0;
unsigned char prioritized = 0;

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
    // R0-R7: output, R5: input
    TRISA = 0b00100000;
    // RB5, RB6, RB7 output
    TRISB = 0b00011111;

    RB5 = 0; // no beep
    
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

void Display(unsigned char num, unsigned char pos)
{
    switch(num)
    {
        case 0:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b01000000;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b01000000;
                RB6 = 1;

            }
            break;
        case 1:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b11100111;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b11100111;
                RB6 = 1;

            }
            break;
        case 2:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b10010000;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b10010000;
                RB6 = 1;

            }
            break;
        case 3:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b10100001;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b10100001;
                RB6 = 1;

            }
            break;
        case 4:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00100111;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00100111;
                RB6 = 1;

            }
            break;
        case 5:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00101001;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00101001;
                RB6 = 1;

            }
            break;
        case 6:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00101000;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00101000;
                RB6 = 1;

            }
            break;
        case 7:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b11100011;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b11100011;
                RB6 = 1;

            }
            break;
        case 8:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00000000;
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00000000;
                RB6 = 1;

            }
            break;
        case 9:
            if(pos == 0)
            {
                RB6 = RB7 = 0;
                PORTA = 0b00000001;//RA2,RA3,RA4,RA1,RA0,RA7,RA6
                RB7 = 1;
            }
            else
            {
                RB6 = RB7 = 0;
                PORTA = 0b00000001;
                RB6 = 1;

            }
            break;
    }
}
void InsertNewIndex(unsigned char num)
{
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

        flick[i] = TIMEOUT_FLICK_IN_SECOND;
        timeout[i] = TIMEOUT_IN_SECOND;

        return;
    }

    if(numNorCount == 0)
    {
        numNorCount++;
    }
    else if(numNorCount == MAX_NUM)
    {
        unsigned char i;
        for(i = 0; i < numNorCount - 1; i++)
        {
            unit[i] = unit[i + 1];
            ten[i] = ten[i + 1];
            flick[i] = flick[i + 1];
            timeout[i] = timeout[i + 1];

            if(curViewIndex == i + 1)
            {
                curViewIndex--;
                moved = 1;
            }
        }
        if(curViewIndex == 0)
        {
            moved = 1;
        }
    }
    else
    {
        curNorIndex++;
        numNorCount++;
    }

    unit[curNorIndex] = t_unit;
    ten[curNorIndex] = t_ten;
    flick[curNorIndex] = TIMEOUT_FLICK_IN_SECOND;
    timeout[curNorIndex] = TIMEOUT_IN_SECOND;

    if(prioritized == 0)
    {
        moved = 1;
        curViewIndex = curNorIndex;
    }

    if(numNorCount == 1)
    {
        beep();
    }
    else
    {
        if(moved == 1)
        {
            if(flick[curViewIndex] == TIMEOUT_FLICK_IN_SECOND)
            {
                beep();
            }
        }
    }

}
unsigned char GetNextIndex(unsigned char index)
{
    if(numNorCount == 0)
    {
        return index;
    }
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
    unsigned char j;
    curFlipFlopTick++;
    if(curFlipFlopTick == TIMEOUT_FLIP_FLOP_IN_TICK)
    {
        curFlipFlopTick = 0;
        if(flick[curViewIndex] > 0)
        {
            visible[curViewIndex] = (visible[curViewIndex] == 0) ? 1: 0;
        }
        else
        {
            visible[curViewIndex] = 1;
        }
    }

    curTick++;
    if(curTick == TICK_PER_SECOND)
    {
        curTick = 0;

        if(flick[curViewIndex] > 0)
        {
            flick[curViewIndex]--;
            prioritized = 1;
            return;
        }
        prioritized = 0;

        if(numNorCount == 0)
        {
            if(timeout[0] == 0)
            {
                curNorIndex = 0;
                curViewIndex = 0;
                unit[0] = 0;
                ten[0] = 0;
                timeout[0] = 0;
            }
            else
            {
                timeout[0]--;
            }
        }
        else
        {
            for(unsigned char i = 0; i < numNorCount; i++)
            {
                if(timeout[i] == 0)
                {
                    if(i == curViewIndex)
                    {
                        moved = 1;
                    }
                    for(j = i; j < numNorCount - 1; j++)
                    {
                        if(curViewIndex == j + 1)
                        {
                            curViewIndex = j;
                            moved = 1;
                        }
                        unit[j] = unit[j + 1];
                        ten[j] = ten[j + 1];
                        flick[j] = flick[j + 1];
                        timeout[j] = timeout[j + 1];
                    }
                    numNorCount--;
                    curNorIndex = numNorCount - 1;

               }
               else
               {
                   timeout[i]--;
               }

            }

        }
        if(moved == 1)
        {
            if(flick[curViewIndex] == TIMEOUT_FLICK_IN_SECOND)
            {
                beep();
            }
            moved = 0;
        }
        else
        {
            curViewIndex = GetNextIndex(curViewIndex);

            if(flick[curViewIndex] == TIMEOUT_FLICK_IN_SECOND)
            {
                beep();
            }

        }

/*        if(mode == MODE_FLICKER)
        {
            curReviewIndex = GetNextIndex(curReviewIndex);

            numReviewCount++;
        }*/
    }

    if(visible[curViewIndex] == 1)
    {
        Display(unit[index], 0);
        __delay_ms(10);
        Display(ten[index], 1);
        __delay_ms(10);

    }
    else
    {
        RB6 = RB7 = 0;
        __delay_ms(20);
    }
    
/*    if(mode == MODE_FLICKER)
    {
        if(numReviewCount == numNorCount)
        {
//            mode = MODE_NORMAL;
        }

    }*/
}
void main(void)
{
    Init();

    while(1)
    {
        DisplayIndex(curViewIndex);
        //Display(curNorIndex, 0);
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
        if(RB4 == 1)
        {
            InsertNewIndex(PORTB & 0b00001111);
        }
        RBIF = 0;
    }

}
