//#define WINDOW_BASE
#define UART_ENABLE
#define DEBUG_ENABLE  1
#define DEBUG_DISABLE 0


#ifdef WINDOW_BASE
#include <stdint.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#else
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <pic16f886.h>
#include "usart_pic16.h"
#include "myutils.h"
#endif


#ifdef WINDOW_BASE
using namespace std;
#else
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = ON          // Code Protection bit (Program memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#define IOCB_ENABLE      IOCBbits.IOCB4 = 1
#define IOCB_CLEAR       IOCBbits.IOCB4 = 0
#define INTB_ENABLE      INTCONbits.RBIE = 1
#define INTB_FLAG        INTCONbits.RBIF
#define INT_ENABLE       INTCONbits.INTE = 1
#define GLB_INT_ENABLE   INTCONbits.GIE

//LM35 is connected to Port A bit 2

#define TUNE_BUTTON_PORT      B
#define TUNE_BUTTON_POS       4
#define TUNE_BUTTON_PIN       PIN(TUNE_BUTTON_PORT, TUNE_BUTTON_POS)

#define TUNE_BUTTON                     PORTBIT(TUNE_BUTTON_PIN)
#define TUNE_BUTTON_TRIS                TRISBIT(TUNE_BUTTON_PIN)

#define TRIGGER_DOWN_OUT_PORT      A
#define TRIGGER_DOWN_OUT_POS       1
#define TRIGGER_DOWN_OUT_PIN       PIN(TRIGGER_DOWN_OUT_PORT, TRIGGER_DOWN_OUT_POS)
#define TRIGGER_DOWN_OUT           PORTBIT(TRIGGER_DOWN_OUT_PIN)

#define TRIGGER_UP_OUT_PORT      A
#define TRIGGER_UP_OUT_POS       0
#define TRIGGER_UP_OUT_PIN       PIN(TRIGGER_UP_OUT_PORT, TRIGGER_UP_OUT_POS)
#define TRIGGER_UP_OUT           PORTBIT(TRIGGER_UP_OUT_PIN)


#define TUNE_BUTTON_RAISING_EDGE        IOCPBIT(TUNE_BUTTON_PIN)
#define TUNE_BUTTON_IOC_FLAG            IOCFBIT(TUNE_BUTTON_PIN)

#define DATA_PORT         A
#define DATA_POS          3
#define DATA_PIN          PIN(DATA_PORT, DATA_POS)
#define DATA              PORTBIT(DATA_PIN)

#define LOAD_PORT         A
#define LOAD_POS          2
#define LOAD_PIN          PIN(LOAD_PORT, LOAD_POS)
#define LOAD              PORTBIT(LOAD_PIN)

#define CLK_PORT          A
#define CLK_POS           1
#define CLK_PIN           PIN(CLK_PORT, CLK_POS)
#define CLK               PORTBIT(CLK_PIN)

#endif

#define MATRIX44_COLUMN_MAX 4
#define MATRIX44_ROW_MAX 4

#define MATRIX88_COLUMN_MAX 8
#define MATRIX88_ROW_MAX 8

#define CHARACTER_MAX 9

typedef struct 
{
    uint8_t start_index;
    uint8_t cur_index;
    uint8_t num;
} CHARACTER_INFO;

typedef struct 
{
    uint8_t  data[MATRIX44_ROW_MAX][MATRIX44_COLUMN_MAX];
} MATRIX44;
typedef struct 
{
    uint8_t  data[MATRIX88_ROW_MAX][MATRIX88_COLUMN_MAX];
} MATRIX88;

typedef struct 
{
    uint8_t  col[MATRIX88_COLUMN_MAX];
} MATRIX7219;

typedef enum
{
    OK,
    GAME_OVER,
    LEFT_OVER_BOUNDARY,
    RIGHT_OVER_BOUNDARY,
    HIT_LAND
};   

CHARACTER_INFO g_char_info[CHARACTER_MAX] =
{
////////I/////////////
{0, 0, 2},
////////s/////////////
{2, 0, 2},
////////back s/////////////
{4, 0, 2},
////////back L/////////////
{6, 0, 4},
////////L/////////////
{10, 0, 4},
////////box/////////////
{14, 0, 1},
////////V/////////////
{15, 0, 4},
////////+/////////////
{19, 0, 1},
////////T/////////////
{20, 0, 4},
};
uint8_t g_char_info_index;
MATRIX44* g_cur_matrix44;
#ifdef WINDOW_BASE
MATRIX44 g_matrix44[] =
#else
const MATRIX44 g_matrix44[] =
#endif
{
////////I/////////////
{0,	1,	0,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	1,	0,	0},
{0,	0,	0,	0,
1,	1,	1,	1,
0,	0,	0,	0,
0,	0,	0,	0},
////////s/////////////
{0,	1,	1,	0,
1,	1,	0,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	1,	0,
0,	0,	1,	0,
0,	0,	0,	0},
////////back s/////////////
{1,	1,	0,	0,
0,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
1,	1,	0,	0,
1,	0,	0,	0,
0,	0,	0,	0},
////////back L/////////////
{0,	0,	0,	0,
1,	1,	1,	0,
0,	0,	1,	0,
0,	0,	0,	0},
{0,	1,	1,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{1,	0,	0,	0,
1,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	0,	0,
1,	1,	0,	0,
0,	0,	0,	0},
////////L/////////////
{0,	0,	0,	0,
1,	1,	1,	0,
1,	0,	0,	0,
0,	0,	0,	0},
{1,	1,	0,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	0,	1,	0,
1,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	0,	0,
0,	1,	1,	0,
0,	0,	0,	0},
////////box/////////////
{0,	1,	1,	0,
0,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
////////V/////////////
{0,	0,	0,	0,
0,	1,	1,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	0,	0,	0,
1,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
1,	1,	0,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
////////+/////////////
{0,	1,	0,	0,
1,	1,	1,	0,
0,	1,	0,	0,
0,	0,	0,	0},
////////T/////////////
{1,	1,	1,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	0,	1,	0,
1,	1,	1,	0,
0,	0,	1,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	0,	0,
1,	1,	1,	0,
0,	0,	0,	0},
{1,	0,	0,	0,
1,	1,	1,	0,
1,	0,	0,	0,
0,	0,	0,	0},
};         
MATRIX88 g_matrix88 = 
{
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
};
int8_t cur_x = 2;
int8_t cur_y = 0;    

#ifdef WINDOW_BASE
FILE *fp;
#endif
char g_debug[32];

void debug_str(const char* str)
{
#ifdef WINDOW_BASE
	fprintf(fp, str);
#else
#ifdef UART_ENABLE
	USARTWriteString(str);
#endif
#endif
}
void debug_line(const char* str)
{
#ifdef WINDOW_BASE
	fprintf(fp, str);
	fprintf(fp, "\n");
#else
#ifdef UART_ENABLE
	USARTWriteString(str);
	USARTWriteString("\r\n");
#endif
#endif
}

void debug_int1(const char* f, int i)
{
#ifdef WINDOW_BASE
	fprintf(fp, f, i);
	fprintf(fp, "\n");
#else
#ifdef UART_ENABLE
	sprintf(g_debug, f, i);
	USARTWriteString(g_debug);
	USARTWriteString("\r\n");
#endif
#endif
}
void debug_int2(const char* f, int i1, int i2)
{
#ifdef WINDOW_BASE
	fprintf(fp, f, i1, i2);
	fprintf(fp, "\n");
#else
#ifdef UART_ENABLE
	sprintf(g_debug, f, i1, i2);
	USARTWriteString(g_debug);
	USARTWriteString("\r\n");
#endif
#endif
}
void debug_int3(const char* f, int i1, int i2, int i3)
{
#ifdef WINDOW_BASE
	fprintf(fp, f, i1, i2, i3);
	fprintf(fp, "\n");
#else
#ifdef UART_ENABLE
	sprintf(g_debug, f, i1, i2, i3);
	USARTWriteString(g_debug);
	USARTWriteString("\r\n");
#endif
#endif
}
#if DEBUG_ENABLE
void printf_debug_MATRIX44(const char* lable, int8_t x, int8_t y, const MATRIX44* matrix)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    debug_line("<<<<<<<<<<<<<<<<<<<<MATRIX44");
    for(int8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(int8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if((row - y >= 0) && (row - y < MATRIX44_ROW_MAX)
            && (col - x >= 0) && (col - x < MATRIX44_COLUMN_MAX)
            && (matrix->data[row - y][col - x] == 1))
            {
                debug_str("*");
            }
            else
            {
                debug_str("_");
            }
        }
		debug_line("");
    }
	debug_line(">>>>>>>>>>>>>>>>>>>>");
}
void printf_debug_cur_MATRIX44(const char* lable, int8_t x, int8_t y)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    MATRIX44* matrix = &g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info[g_char_info_index].cur_index];
    printf_debug_MATRIX44(NULL, x, y, matrix);
}
#endif
MATRIX44* get_MATRIX44(uint8_t index, uint8_t sub_index)
{
    return &g_matrix44[g_char_info[index].start_index + sub_index];
}
#if DEBUG_ENABLE
void printf_debug_all_MATRIX44()
{
	MATRIX44* matrix;
    debug_line("printf_all_MATRIX44");
    debug_int1("size = %d", CHARACTER_MAX);

    for(uint8_t index = 0; index < CHARACTER_MAX; index++)
    {
        for(uint8_t sub_index = 0; sub_index < g_char_info[index].num; sub_index++)
        {
            debug_int2("index = %d, sub_index = %d", index, sub_index);

        	matrix = get_MATRIX44(index, sub_index);
            printf_debug_MATRIX44(NULL, 0, 0, matrix);
        }
    }
}     
#endif
#ifndef WINDOW_BASE
void SPI1_write(uint8_t data) 
{
    uint8_t mask = 0b10000000;
    for(uint8_t i = 0; i < 8; i++)
    {
        if((data & mask) > 0)
        {
            DATA = 1;
//            USARTWriteLine("1");
        }
        else
        {
            DATA = 0;
//            USARTWriteLine("0");
        }
        mask >>= 1;
        CLK = 1;
        __delay_us(10);
        CLK = 0;
        __delay_us(10);

    }
}
// This is write Byte function.

void Write_Byte(uint8_t myColumn, uint8_t myValue)
{
    LOAD = 0; // select max7219.
    SPI1_write(myColumn); // send myColumn value to max7219 (digit place).
    SPI1_write(myValue); // send myValue value to max7219 (digit place).
    LOAD = 1; // deselect max7219.
}
// Here we set the configuration of max7219.
void max7219_init1()
{
	Write_Byte(0x09, 0x00);
	Write_Byte(0x0A, 0x0F);
	Write_Byte(0x0B, 0x07);
	Write_Byte(0x0C, 0x01);
	Write_Byte(0x00, 0xFF);
}
#endif
void MATRIX88_to_MATRIX7219(const MATRIX88* matrix88, MATRIX7219* matrix7219)
{
    uint8_t mask = 0x80;

    for(uint8_t col = 0; col < MATRIX88_ROW_MAX; col++)
    {
        mask = 0x80;
        matrix7219->col[col] = 0;
        for(uint8_t row = 0; row < MATRIX88_COLUMN_MAX; row++)
        {
            if(matrix88->data[row][col] == 1)
            {
                matrix7219->col[col] |= mask;
            }
            mask >>= 1;
        }
    }
}
#if DEBUG_ENABLE
void printf_debug_MATRIX88(const char* lable, const MATRIX88* matrix)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    debug_line("<<<<<<<<<<<<<<<<<<<<MATRIX88");
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix->data[row][col] == 1)
            {
                debug_str("*");
            }
            else
            {
                debug_str("_");
            }
        }
        debug_line("");
    }
    debug_line(">>>>>>>>>>>>>>>>>>>>");
}
#endif
#if DEBUG_ENABLE
#ifdef WINDOW_BASE
void printf_debug_MATRIX7219(const char* lable, const MATRIX7219* matrix)
{
    uint8_t mask = 0x80;

	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    debug_line("<<<<<<<<<<<<<<<<<<<<");

    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if((matrix->col[col] & mask) > 0)
            {
                debug_str("*");
            }
            else
            {
                debug_str("_");
            }
        }

        debug_line("");
        mask >>= 1;
    }
    debug_line(">>>>>>>>>>>>>>>>>>>>");
}
#else
void printf_MATRIX7219(const MATRIX7219* matrix)
{
    uint8_t col;

    for (col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        Write_Byte(col + 1, matrix->col[col]);
    }
}

#endif
#endif

void printf_MATRIX88(const MATRIX88* matrix88)
{
#ifdef WINDOW_BASE
    printf("<<<<<<<<<<<<<<<<<<<<MATRIX88\n");
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix88->data[row][col] == 1)
            {
            	printf("*");
            }
            else
            {
            	printf("_");
            }
        }
        printf("\n");
    }
    printf(">>>>>>>>>>>>>>>>>>>>\n");

#else
    MATRIX7219 matrix7219;
    MATRIX88_to_MATRIX7219(matrix88, &matrix7219);
    printf_MATRIX7219(&matrix7219);
#endif
}
void printf_Screen()
{
    printf_MATRIX88(&g_matrix88);
}
#if DEBUG_ENABLE
void printf_debug_Screen(const char* lable)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    printf_debug_MATRIX88(NULL, &g_matrix88);
}
#endif
// This is clear matrix function.
void Clear_Matrix(void) 
{
    memset(&g_matrix88, 0, sizeof(MATRIX88));
    printf_Screen();
}

uint8_t is_row_full(const MATRIX88* matrix, uint8_t row)
{
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        if(matrix->data[row][col] == 0)
        {
            return 0;
        }
    }
    return 1;
}
void delete_row(MATRIX88* matrix, uint8_t row)
{
    for(int8_t i = MATRIX88_ROW_MAX - 1; i >= 0; i--)
    {
        if(i <= row)
        {
            if(i > 0)
            {
#ifdef WINDOW_BASE
    size_t len;
#else
    register size_t len;
#endif                
                len = MATRIX88_COLUMN_MAX*sizeof(uint8_t);
                memcpy(matrix->data[i], matrix->data[i - 1], len);
            }
            else
            {
                memset(matrix->data[i], 0, MATRIX88_COLUMN_MAX*sizeof(uint8_t));
            }
        }
    }     
}
uint8_t delete_matrix(MATRIX88* matrix)
{
    uint8_t count = 0;
    int8_t row = MATRIX88_ROW_MAX - 1;
    while(row >= 0)
    {
        if(is_row_full(matrix, row))
        {
            delete_row(matrix, row);
            count++;
        }
        else
        {
            row--;            
        }
    }
#if DEBUG_DISABLE
    debug_int1("delete_matrix count = %d", count);
#endif
    return count;
}
uint8_t get_num_removed_rows(MATRIX88* matrix)
{
    uint8_t count = 0;
    for(int8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        if(is_row_full(matrix, row) == 1)
        {
            count++;
        }
    }
#if DEBUG_DISABLE
    debug_int1("num full rows = %d", count);
#endif
    return count;
}

uint8_t is_row_empty(const MATRIX88* matrix, uint8_t row)
{
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        if(matrix->data[row][col] == 1)
        {
            return 0;
        }
    }
    return 1;
}
uint8_t is_col_empty(const MATRIX88* matrix, uint8_t col)
{
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        if(matrix->data[row][col] == 1)
        {
            return 0;
        }
    }
    return 1;
}
uint8_t hit_land(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
#if DEBUG_DISABLE
    debug_line("==============hit_land============");
#endif

    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if((y + row) >= (MATRIX88_ROW_MAX - 1))
                {
#if DEBUG_DISABLE
                    debug_int2("hit1 row = %d, col = %d", row, col);
#endif
                    return 1;
                }    

                if(matrix88->data[y + row + 1][x + col] == 1)
                {
#if DEBUG_DISABLE
                    debug_int2("hit2 row = %d, col = %d", row, col);
#endif
                    return 1;
                }    
            }                             
        }            
    } 
#if DEBUG_DISABLE
    debug_line("not hit");
#endif
    return 0;
} 
uint8_t is_valid(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
#if DEBUG_DISABLE
    debug_line("==============is_valid============");
#endif
    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if(matrix88->data[y + row][x + col] == 1)
                {
#if DEBUG_DISABLE
                    debug_line("not valid1");
                    debug_int2("row = %d, col = %d", row, col);
#endif
                    return 0;
                }

                if(( x + col < 0) || (x + col >= MATRIX88_COLUMN_MAX))
                {
#if DEBUG_DISABLE
                    debug_line("not valid2");
                    debug_int2("row = %d, col = %d", row, col);
#endif
                    return 0;
                }
                if((y + row) > (MATRIX88_ROW_MAX - 1))
                {
#if DEBUG_DISABLE
                    debug_line("not valid3");
                    debug_int2("row = %d, col = %d", row, col);
#endif
                    return 0;
                }
            }
        }
    }
#if DEBUG_DISABLE
    debug_line("valid");
#endif
    return 1;
}
uint8_t is_left_boundary(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if( x + col < 0)
                {
#if DEBUG_DISABLE
                    debug_line("LEFT_OVER_BOUNDARY");
#endif
                    return LEFT_OVER_BOUNDARY;
                }    
            }                             
        }            
    } 
    return OK;
}     
uint8_t is_right_boundary(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if(x + col > MATRIX88_COLUMN_MAX - 1)
                {
#if DEBUG_DISABLE
                    debug_line("RIGHT_OVER_BOUNDARY");
#endif
                    return RIGHT_OVER_BOUNDARY;
                }    
            }                             
        }            
    } 
    return OK;
}     
uint8_t fall_off(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    while(1)
    {
        for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
        {
            for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
            {
                if(matrix44->data[row][col] == 1)
                {
                    if(matrix88->data[y + row + 1][x + col] == 1)
                    {
#if DEBUG_DISABLE
                        debug_line("fall_off1");
                        debug_int2("x = %d, y = %d", x, y);
#endif
                        return y;
                    }    
                    if((y + row) >= (MATRIX88_ROW_MAX - 1))
                    {
#if DEBUG_DISABLE
                        debug_line("fall_off2");
                        debug_int2("x = %d, y = %d", x, y);
#endif
                        return y;
                    }  
                }                             
            }            
        } 
        y++;
    }
} 
void clear(int8_t x, int8_t y, const MATRIX44* matrix44, MATRIX88* matrix88)
{
    for(uint8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                matrix88->data[y + row][x + col] = 0;                         
            }                             
        }            
    }            
}     
void merge(int8_t x, int8_t y, const MATRIX44* matrix44, MATRIX88* matrix88)
{
    for(uint8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                matrix88->data[y + row][x + col] = 1;                         
            }                             
        }            
    }            
}     
void merge1(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88_in, MATRIX88* matrix88_out)
{
#ifdef WINDOW_BASE
    size_t len;
#else
    register size_t len;
#endif    
    len = sizeof(MATRIX88);
    memcpy(matrix88_out, matrix88_in, len);

    for(uint8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                matrix88_out->data[y + row][x + col] = 1;                         
            }                             
        }            
    }            
}     
uint16_t get_num_of_orphan(const MATRIX88* matrix)
{
    uint16_t risk = 0;
    uint8_t full = 0xFF;
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        full = 0xFF;
        for(int8_t row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
        {
            if(full == 0xFF)
            {
                full = matrix->data[row][col];
            }
            else
            {
                if(matrix->data[row][col] == 1)
                {
                    if(full == 0)
                    {
                        risk++;
                    }
                }
                full = matrix->data[row][col];
            }
        }
    }
#if DEBUG_DISABLE
    debug_int1("risk = %d", risk);
#endif

    return risk;
}
uint16_t get_heavy(const MATRIX88* matrix)
{
	uint8_t start;
    uint16_t risk = 0;
    uint8_t pre = 0xFF;
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
    	pre = 0xFF;
        start = 0;
        for(int8_t row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
        {
        	if(pre == 0xFF)
        	{
        		pre = matrix->data[row][col];
        	}
        	else
        	{
                if(pre != matrix->data[row][col])
                {
                	pre = matrix->data[row][col];
                	if(pre == 0)
                	{
                		start = 0;
                	}
                	else
                	{
                		start = 1;
                	}
                }
                if(start == 1)
                {
                    risk++;
                }
        	}
        }
    }
#if DEBUG_DISABLE
    debug_int1("risk = %d", risk);
#endif

    return risk;
}

uint8_t char_info_index_rand()
{
    return (uint8_t)(rand()%CHARACTER_MAX);
}
int8_t left_most(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    while(1)
    {
        if(is_left_boundary(x, matrix44, matrix88) == LEFT_OVER_BOUNDARY)
        {
#if DEBUG_DISABLE
            debug_int1("left_most = %d", x + 1);
#endif
            return x + 1;
        }
        x--;
    } 
}    
int8_t right_most(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    while(1)
    {
        if(is_right_boundary(x, matrix44, matrix88) == RIGHT_OVER_BOUNDARY)
        {
#if DEBUG_DISABLE
            debug_int1("right_most = %d", x - 1);
#endif
            return x - 1;
        }
        x++;
    } 
}    
uint8_t get_high(MATRIX88* matrix)
{
    for(int8_t row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
    {
        if(is_row_empty(matrix, row) == 1)
        {
#if DEBUG_DISABLE
            debug_int1("get_high height = %d", MATRIX88_ROW_MAX - row - 1);
#endif
            return (uint8_t)(MATRIX88_ROW_MAX - row - 1);
        }
    } 
    return MATRIX88_ROW_MAX;    
}
uint8_t get_high_after_merge(int8_t y, MATRIX44* matrix)
{
#if DEBUG_DISABLE
    debug_line("get_high_after_merge");
#endif
    for(int8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
        	if(matrix->data[row][col] == 1)
        	{
#if DEBUG_DISABLE
                debug_int1("y = %d", y);
                debug_int1("row = %d", row);
                debug_int1("height = %d", MATRIX88_ROW_MAX - y - row);
#endif
                return (uint8_t)(MATRIX88_ROW_MAX - y - row);
        	}
        }
    }
}
uint8_t get_holes_after_merge(MATRIX88* matrix)
{
	int8_t start = -1;
	int8_t stop = -1;
	uint8_t num_hole = 0;
    for(int8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
    	start = stop = -1;
        for(int8_t row = 0; row < MATRIX88_ROW_MAX; row++)
        {
        	if(col == 0)
        	{
        		if((matrix->data[row][col] == 0) && (matrix->data[row][col + 1] == 1))
        		{
        			if(start == -1)
        			{
            			start = row;
        			}
        		}
        	}
        	else if(col == MATRIX88_COLUMN_MAX - 1)
        	{
        		if((matrix->data[row][col] == 0) && (matrix->data[row][col - 1] == 1))
        		{
        			if(start == -1)
        			{
            			start = row;
        			}
        		}
        	}
        	else
        	{
        		if((matrix->data[row][col] == 0) && (matrix->data[row][col - 1] == 1) && (matrix->data[row][col + 1] == 1))
        		{
        			if(start == -1)
        			{
            			start = row;
        			}
        		}
        	}
    		if(start >= 0)
    		{
        		if(row == MATRIX88_ROW_MAX - 1)
        		{
        			if(stop == -1)
        			{
            			stop = MATRIX88_ROW_MAX;
        			}
        		}
        		else if(matrix->data[row + 1][col] == 1)
        		{
        			if(stop == -1)
        			{
            			stop = row + 1;
        			}
        		}
    		}

        }
        if((start >= 0) && (stop >= 0) && (stop - start >= 3))
        {
#if DEBUG_DISABLE
            debug_int1("col = %d", col);
            debug_int1("start = %d", start);
            debug_int1("stop = %d", stop);
#endif
        	num_hole++;
        }
    }
#if DEBUG_DISABLE
    debug_int1("num_hole = %d", num_hole);
#endif
    return num_hole;
}
MATRIX44* temp_cur_matrix44;
MATRIX88 temp_matrix88;
uint8_t find_best_solution()
{
#if DEBUG_DISABLE
    debug_line("===find_best_solution===");
#endif

    uint8_t res = 0;
    int8_t left_most_index, right_most_index;

    int8_t temp_pre_x = 0xF, tem_pre_sub_index = 0xF;
    int16_t temp_pre_risk = -30000;
    int8_t temp_y;
    int16_t temp_risk;
    uint16_t temp_high;

    //    debug_int2("g_char_info_index = (%d), num = %d", g_char_info_index, g_char_info[g_char_info_index].num);
    for(uint8_t tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
    {
        temp_cur_matrix44 = &g_matrix44[g_char_info[g_char_info_index].start_index + tem_sub_index];
        left_most_index = left_most(cur_x, temp_cur_matrix44, &g_matrix88);
        right_most_index = right_most(cur_x, temp_cur_matrix44, &g_matrix88);

        for(int8_t temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
        {
            temp_y = fall_off(temp_x, cur_y, temp_cur_matrix44, &g_matrix88); 

#if DEBUG_DISABLE
            printf_debug_MATRIX44("After fall off", temp_x, temp_y, temp_cur_matrix44);
            printf_debug_Screen("After fall off");
#endif

            if(is_valid(temp_x, temp_y, temp_cur_matrix44, &g_matrix88) == 0)
            {
                continue;
            }
            res = 1;
            merge1(temp_x, temp_y, temp_cur_matrix44, &g_matrix88, &temp_matrix88); 
            temp_high = get_high_after_merge(temp_y, temp_cur_matrix44);
            if((get_high(&g_matrix88) <= MATRIX88_ROW_MAX/2 + 1)
            && (temp_high <= MATRIX88_ROW_MAX/2 + 1))
            {
                temp_risk = (((int16_t)get_num_removed_rows(&temp_matrix88)) << 10)
                		   - get_num_of_orphan(&temp_matrix88)*4
    					   - temp_high*3
    					   - get_holes_after_merge(&temp_matrix88)*2
						   - get_heavy(&temp_matrix88);
            }
            else
            {
                temp_risk = (((int16_t)get_num_removed_rows(&temp_matrix88)) << 10)
                		   - get_num_of_orphan(&temp_matrix88)*2
    					   - temp_high*5
    					   - get_holes_after_merge(&temp_matrix88)*3
						   - get_heavy(&temp_matrix88);
            }
#if DEBUG_DISABLE
            printf_debug_MATRIX88("Valid instance", &temp_matrix88);
            debug_line("Start evaluation");
#endif

#if DEBUG_DISABLE
            debug_int1("temp_risk = %d", temp_risk);
#endif
            if(temp_risk > temp_pre_risk)
            {
#if DEBUG_DISABLE
                debug_int2("risk: (%d) > (%d)", temp_risk, temp_pre_risk);
#endif
    			temp_pre_risk = temp_risk;
    			tem_pre_sub_index = tem_sub_index;
    			temp_pre_x = temp_x;
            }

#if DEBUG_DISABLE
#ifdef WINDOW_BASE
            fprintf(fp, "sub_index = %d, temp_pre_x = %d, temp_pre_risk = %d",
            		tem_pre_sub_index, temp_pre_x, temp_pre_risk);
            //			system("PAUSE");
#else
            debug_line("Loop");
            debug_int1("sub_index = %d", tem_pre_sub_index);
            debug_int1("temp_pre_x = %d", temp_pre_x);
            debug_int1("temp_pre_risk = %d", temp_pre_risk);
#endif
#endif
        }
    } 
    if(res == 1)
    {
        g_char_info[g_char_info_index].cur_index = tem_pre_sub_index;
        cur_x = temp_pre_x;
#if DEBUG_DISABLE
        printf_debug_cur_MATRIX44("Chosen", cur_x, cur_y);
#ifdef WINDOW_BASE

        fprintf(fp, "chosen sub_index = %d, temp_pre_x = %d, temp_pre_risk = %d",
        		tem_pre_sub_index, temp_pre_x, temp_pre_risk);
#else
        debug_line("Chosen");
        debug_int1("sub_index = %d", tem_pre_sub_index);
        debug_int1("temp_pre_x = %d", temp_pre_x);
        debug_int1("temp_pre_risk = %d", temp_pre_risk);
#endif
#endif
    }
    else
    {
#if DEBUG_DISABLE
    	debug_line("GAME OVER!!!");
#endif
    }
    return res;
}
#ifdef WINDOW_BASE
void test_is_row_full(const MATRIX88* matrix)
{
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_full(matrix, row) == 0 ? "not full" : "full");
    }
}
void test_is_row_empty(const MATRIX88* matrix)
{
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_empty(matrix, row) == 0 ? "not empty" : "empty");
    }
}
void test_is_col_empty(const MATRIX88* matrix)
{
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        fprintf(fp, "col[%d] is %s\n", col, is_col_empty(matrix, col) == 0 ? "not empty" : "empty");
    }
}
void test_hit_land()
{
    int8_t x = 5, y = 6;
    MATRIX44* matrix44 = get_MATRIX44(1, 0);
    MATRIX88 matrix88 =
    {
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  1,  0,  1,  0,  0,  0,  0,
            1,  0,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  0,  1,  0,  0,  0,
    };
    printf_debug_MATRIX44(NULL, x, y, matrix44);
    printf_debug_MATRIX88(NULL, &matrix88);
    hit_land(x, y, matrix44, &matrix88);
}
void test_is_valid()
{
    int8_t x = 5, y = 7;
    MATRIX44* matrix44 = get_MATRIX44(1, 0);
    MATRIX88 matrix88 =
    {
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  1,  0,  1,  0,  0,  0,  0,
            1,  0,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  0,  1,  0,  0,  0,
    };
    printf_debug_MATRIX44(NULL, x, y, matrix44);
    printf_debug_MATRIX88(NULL, &matrix88);
    is_valid(x, y, matrix44, &matrix88);
}
void test_find_best_solution()
{
    g_char_info_index = 1;
    find_best_solution();
}
void test_get_holes_after_merge()
{
    MATRIX88 matrix88 =
    {
    		0,	0,	0,	0,	0,	0,	0,	0,
    		0,	0,	0,	0,	0,	0,	0,	0,
    		0,	0,	0,	0,	0,	0,	0,	0,
    		0,	0,	0,	0,	0,	0,	1,	0,
    		0,	0,	1,	0,	1,	0,	1,	0,
    		0,	1,	1,	0,	1,	0,	1,	0,
    		0,	1,	1,	0,	1,	0,	1,	0,
    		0,	1,	1,	1,	1,	1,	1,	0,
    };
    printf_MATRIX88(&matrix88);
    get_holes_after_merge(&matrix88);
}
#endif


// Here we have the main function.

int main(int argc, char *argv[])
{
    uint8_t hit_res;
#ifdef WINDOW_BASE
    //////////////////////////////////////////////
    fp = fopen("debug.txt", "w");
    if(fp==NULL)
    {
        fprintf(fp, "File Not Found");
        exit(-1);
    }

    srand(time(NULL));
#else
    IO_OUTPUT(DATA_PIN);

    IO_OUTPUT(LOAD_PIN);

    IO_OUTPUT(CLK_PIN);
    
    ANSELbits.ANS1 = 0;
    ANSELbits.ANS2 = 0;
    ANSELbits.ANS3 = 0;
    LOAD = 1;
    CLK = 0;
    
//    //Initialize USART with baud rate 9600
#ifdef UART_ENABLE
    USARTInit(9600);
#endif
//    USARTWriteLine("***********************************************");
#ifndef WINDOW_BASE
    max7219_init1(); // initialize  max7219.
#endif
    unsigned Seed;
	srand(Seed);
#endif
__start:
    Clear_Matrix();
    while(1)
    {
        cur_y = 0;
        cur_x = 2, cur_y = 0;
        g_char_info_index = char_info_index_rand();

#if DEBUG_DISABLE
        debug_int1("g_char_info_index = %d", g_char_info_index);
#endif
        if(find_best_solution() == 0)
        {
#if DEBUG_DISABLE
            debug_line("GAME OVER!!!");
#endif
            goto __start;
        }
        g_cur_matrix44 = &g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info[g_char_info_index].cur_index];
        while(1)
        {
            hit_res = hit_land(cur_x, cur_y, g_cur_matrix44, &g_matrix88);
#if DEBUG_DISABLE
            debug_int1("hit_res = %d", hit_res);
#endif
            merge(cur_x, cur_y, g_cur_matrix44, &g_matrix88);
            if(hit_res == 1)
            {
                printf_Screen();
#ifdef WINDOW_BASE
                Sleep(100);
#else
                __delay_ms(100);
#endif
                delete_matrix(&g_matrix88);
            }
#if DEBUG_ENABLE
            printf_debug_MATRIX88("Main screen", &g_matrix88);
#endif
            printf_Screen();
            if(hit_res == 0)
            {
                clear(cur_x, cur_y, g_cur_matrix44, &g_matrix88);
            }
            else
            {
                break;
            }
#ifdef WINDOW_BASE
            Sleep(500);
#else
            __delay_ms(500);
#endif
            cur_y++;
        }
    }
__exit:

#ifdef WINDOW_BASE
    fclose(fp);
    system("PAUSE");
    return EXIT_SUCCESS;
#else
    return 0;
#endif
}
