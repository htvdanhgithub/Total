//#define WINDOW_BASE

#ifndef WINDOW_BASE
#define UART_ENABLE
#endif

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

#define MATRIX4x4_COLUMN_MAX 	4
#define MATRIX4x4_ROW_MAX 		4

#define MATRIX8x8_ROW_MAX 		8
#define MATRIX8x8_COLUMN_MAX 	8

#define MATRIX16x8_COLUMN_MAX 	8
#define MATRIX16x8_ROW_MAX 		16

#define CHARACTER_MAX 			9

typedef struct 
{
    uint8_t start_index;
    uint8_t num;
} CHARACTER_INFO;

typedef struct 
{
    uint8_t  row[MATRIX4x4_ROW_MAX];
} MATRIX4x4;
typedef struct 
{
    uint8_t  row[MATRIX16x8_ROW_MAX];
} MATRIX16x8;

typedef struct 
{
    uint8_t  col1[MATRIX16x8_COLUMN_MAX];
    uint8_t  col2[MATRIX16x8_COLUMN_MAX];
} MATRIX7219;

typedef enum
{
    OK,
    GAME_OVER,
    LEFT_OVER_BOUNDARY,
    RIGHT_OVER_BOUNDARY,
    HIT_LAND
};   
MATRIX16x8 g_matrix16x8 =
{
	{0x0,
	0x0,
	0x0,
	0x40,
	0x54,
	0x56,
	0x56,
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E},
};

#ifdef WINDOW_BASE
CHARACTER_INFO g_char_info[CHARACTER_MAX] =
#else
const CHARACTER_INFO g_char_info[CHARACTER_MAX] =
#endif
{
////////I/////////////
{0, 2},
////////s/////////////
{2, 2},
////////back s/////////////
{4, 2},
////////back L/////////////
{6, 4},
////////L/////////////
{10, 4},
////////box/////////////
{14, 1},
////////V/////////////
{15, 4},
////////+/////////////
{19, 1},
////////T/////////////
{20, 4},
};
uint8_t g_char_info_index;
uint8_t g_char_info_sub_index;
MATRIX4x4* g_cur_matrix4x4;
#ifdef WINDOW_BASE
MATRIX4x4 g_matrix4x4[] =
#else
const MATRIX4x4 g_matrix4x4[] =
#endif
{
////////I/////////////
	{0x2,
	0x2,
	0x2,
	0x2},

	{0x0,
	0xF,
	0x0,
	0x0},

////////s/////////////
	{0x6,
	0x3,
	0x0,
	0x0},

	{0x2,
	0x6,
	0x4,
	0x0},

////////back s/////////////
	{0x3,
	0x6,
	0x0,
	0x0},

	{0x2,
	0x3,
	0x1,
	0x0},

////////back L/////////////
	{0x0,
	0x7,
	0x4,
	0x0},

	{0x6,
	0x2,
	0x2,
	0x0},

	{0x1,
	0x7,
	0x0,
	0x0},

	{0x2,
	0x2,
	0x3,
	0x0},

////////L/////////////
	{0x0,
	0x7,
	0x1,
	0x0},

	{0x3,
	0x2,
	0x2,
	0x0},

	{0x4,
	0x7,
	0x0,
	0x0},

	{0x2,
	0x2,
	0x6,
	0x0},

////////box/////////////
	{0x3,
	0x3,
	0x0,
	0x0},

////////V/////////////
	{0x0,
	0x6,
	0x2,
	0x0},

	{0x0,
	0x3,
	0x2,
	0x0},

	{0x2,
	0x3,
	0x0,
	0x0},

	{0x2,
	0x6,
	0x0,
	0x0},

////////+/////////////
	{0x2,
	0x7,
	0x2,
	0x0},

////////T/////////////
	{0x7,
	0x2,
	0x2,
	0x0},

	{0x4,
	0x7,
	0x4,
	0x0},

	{0x2,
	0x2,
	0x7,
	0x0},

	{0x1,
	0x7,
	0x1,
	0x0},
};         
int8_t cur_x = 2;
int8_t cur_y = 0;    

#ifdef WINDOW_BASE
FILE *fp;
#endif
#ifndef WINDOW_BASE
#ifdef UART_ENABLE
char g_debug[64];
#endif
#endif

#ifndef WINDOW_BASE
#define SEED_EEPROM_INDEX 0
unsigned Seed;
#endif

typedef struct
{
    uint8_t b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
} t_byte;
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

void setbit(uint8_t *byte, uint8_t at, uint8_t value)
{
	t_byte *temp = (t_byte *)byte;
	switch(at)
	{
	case 0:
		temp->b0 = value;
		break;
	case 1:
		temp->b1 = value;
		break;
	case 2:
		temp->b2 = value;
		break;
	case 3:
		temp->b3 = value;
		break;
	case 4:
		temp->b4 = value;
		break;
	case 5:
		temp->b5 = value;
		break;
	case 6:
		temp->b6 = value;
		break;
	case 7:
		temp->b7 = value;
		break;
	}
}
uint8_t getbit(const uint8_t *byte, uint8_t at)
{
	t_byte *temp = (t_byte *)byte;
	switch(at)
	{
	case 0:
		return (uint8_t)temp->b0;
		break;
	case 1:
		return (uint8_t)temp->b1;
		break;
	case 2:
		return (uint8_t)temp->b2;
		break;
	case 3:
		return (uint8_t)temp->b3;
		break;
	case 4:
		return (uint8_t)temp->b4;
		break;
	case 5:
		return (uint8_t)temp->b5;
		break;
	case 6:
		return (uint8_t)temp->b6;
		break;
	case 7:
		return (uint8_t)temp->b7;
		break;
	}
}
void set_matrix_bit(uint8_t *byte, uint8_t row, uint8_t col, uint8_t value)
{
	setbit(&byte[row], col, value);
}
uint8_t get_matrix_bit(const uint8_t *byte, uint8_t row, uint8_t col)
{
#if DEBUG_DISABLE
	debug_int2("row[%d] = %d", row, byte[row]);
	debug_int3("row[%d][%d] = %d", row, col, getbit(&byte[row], col));
#endif
	return getbit(&byte[row], col);
}
#if DEBUG_ENABLE
void printf_debug_MATRIX4x4(const char* lable, int8_t x, int8_t y, const MATRIX4x4* matrix)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    debug_line("<<<<<<<<<<<<<<<<<<<<MATRIX4x4");
    for(int8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
    {
        for(int8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
        {
            if((row - y >= 0) && (row - y < MATRIX4x4_ROW_MAX)
            && (col - x >= 0) && (col - x < MATRIX4x4_COLUMN_MAX)
            && (get_matrix_bit(matrix->row, row - y, col - x) == 1))
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
void printf_debug_cur_MATRIX4x4(const char* lable, int8_t x, int8_t y)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    MATRIX4x4* matrix = &g_matrix4x4[g_char_info[g_char_info_index].start_index + g_char_info_sub_index];
    printf_debug_MATRIX4x4(NULL, x, y, matrix);
}
#endif
MATRIX4x4* get_MATRIX4x4(uint8_t index, uint8_t sub_index)
{
    return &g_matrix4x4[g_char_info[index].start_index + sub_index];
}
#if DEBUG_ENABLE
void printf_debug_all_MATRIX4x4()
{
	MATRIX4x4* matrix;
    debug_line("printf_all_MATRIX4x4");
    debug_int1("size = %d", CHARACTER_MAX);

    for(uint8_t index = 0; index < CHARACTER_MAX; index++)
    {
        for(uint8_t sub_index = 0; sub_index < g_char_info[index].num; sub_index++)
        {
            debug_int2("index = %d, sub_index = %d", index, sub_index);

        	matrix = get_MATRIX4x4(index, sub_index);
            printf_debug_MATRIX4x4(NULL, 0, 0, matrix);
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

void Write_Word(uint8_t myColumn1, uint8_t myValue1, uint8_t myColumn2, uint8_t myValue2)
{
    LOAD = 0; // select max7219.
    SPI1_write(myColumn1); // send myColumn value to max7219 (digit place).
    SPI1_write(myValue1); // send myValue value to max7219 (digit place).
    SPI1_write(myColumn2); // send myColumn value to max7219 (digit place).
    SPI1_write(myValue2); // send myValue value to max7219 (digit place).
    LOAD = 1; // deselect max7219.
}
// Here we set the configuration of max7219.
void max7219_init1()
{
	Write_Word(0x09, 0x00, 0x09, 0x00);
	Write_Word(0x0A, 0x0F, 0x0A, 0x0F);
	Write_Word(0x0B, 0x07, 0x0B, 0x07);
	Write_Word(0x0C, 0x01, 0x0C, 0x01);
	Write_Word(0x00, 0xFF, 0x00, 0xFF);
}

#endif
void MATRIX16x8_to_MATRIX7219(const MATRIX16x8* matrix16x8, MATRIX7219* matrix7219)
{
    uint8_t mask = 0x80;
    uint8_t row;

    for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
    {
        mask = 0x80;
        matrix7219->col1[col] = 0;
        for(row = 0; row < MATRIX8x8_ROW_MAX; row++)
        {
            if(get_matrix_bit(matrix16x8->row, row, col) == 1)
            {
                matrix7219->col1[col] |= mask;
            }
            mask >>= 1;
        }
        mask = 0x80;
        matrix7219->col2[col] = 0;
        for(row = MATRIX8x8_ROW_MAX; row < MATRIX16x8_ROW_MAX; row++)
        {
            if(get_matrix_bit(matrix16x8->row, row, col) == 1)
            {
                matrix7219->col2[col] |= mask;
            }
            mask >>= 1;
        }
    }
}
#if DEBUG_ENABLE
void printf_debug_MATRIX16x8(const char* lable, const MATRIX16x8* matrix)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    debug_line("<<<<<<<<<<<<<<<<<<<<MATRIX16x8");
    for(uint8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix->row, row, col) == 1)
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
void printf_debug_MATRIX7219(const char* lable, const MATRIX7219* matrix)
{
    uint8_t mask = 0x80;
    uint8_t row;
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    debug_line("<<<<<<<<<<<<<<<<<<<<");

    for(row = 0; row < MATRIX8x8_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
        {
            if((matrix->col1[col] & mask) > 0)
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
    for(row = 0; row < MATRIX8x8_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
        {
            if((matrix->col2[col] & mask) > 0)
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
#endif
#ifndef WINDOW_BASE
void printf_MATRIX7219(const MATRIX7219* matrix)
{
    uint8_t col;

    for (col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
    {
        Write_Word(col + 1, matrix->col1[col], col + 1, matrix->col2[col]);
    }
}
#endif
void printf_MATRIX16x8(const MATRIX16x8* matrix16x8)
{
#ifdef WINDOW_BASE
    printf("<<<<<<<<<<<<<<<<<<<<MATRIX16x8\n");
    for(uint8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix16x8->row, row, col) == 1)
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
    MATRIX16x8_to_MATRIX7219(matrix16x8, &matrix7219);
    printf_MATRIX7219(&matrix7219);
#endif
}
void printf_Screen()
{
    printf_MATRIX16x8(&g_matrix16x8);
}
#if DEBUG_ENABLE
void printf_debug_Screen(const char* lable)
{
	if(lable != NULL)
	{
	    debug_str(lable);
	    debug_line(":");
	}
    printf_debug_MATRIX16x8(NULL, &g_matrix16x8);
}
#endif
// This is clear matrix function.
void Clear_Matrix(void) 
{
    memset(&g_matrix16x8, 0, sizeof(MATRIX16x8));
    printf_Screen();
}

uint8_t is_row_full(const MATRIX16x8* matrix, uint8_t row)
{
    if(matrix->row[row] == 0xFF)
    {
#if DEBUG_DISABLE
    	debug_int1("row = %X\n", matrix->row[row]);
        debug_int1("row(%d) is full", row);
    	printf_debug_MATRIX16x8("Row is full", matrix);

#endif

        return 1;
    }
    return 0;
}
void delete_row(MATRIX16x8* matrix, uint8_t row)
{
    for(int8_t i = MATRIX16x8_ROW_MAX - 1; i >= 0; i--)
    {
        if(i <= row)
        {
            if(i > 0)
            {
    			matrix->row[i] = matrix->row[i - 1];
            }
            else
            {
            	matrix->row[i] = 0x0;
            }
        }
    }     
}
uint8_t delete_matrix(MATRIX16x8* matrix)
{
    uint8_t count = 0;
    int8_t row = MATRIX16x8_ROW_MAX - 1;
    while(row >= 0)
    {
#ifndef WINDOW_BASE
    	Seed++;
#endif

        if(is_row_full(matrix, row) == 1)
        {
#if DEBUG_DISABLE
        	printf_debug_MATRIX16x8("Before delete MATRIX16x8", &g_matrix16x8);
#endif
            delete_row(matrix, row);
#if DEBUG_DISABLE
        	printf_debug_MATRIX16x8("After delete MATRIX16x8", &g_matrix16x8);
#endif
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
uint8_t get_num_removed_rows(MATRIX16x8* matrix)
{
    uint8_t count = 0;
    for(int8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
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

uint8_t is_row_empty(const MATRIX16x8* matrix, uint8_t row)
{
    if(matrix->row == 0x0)
    {
        return 1;
    }
    return 0;
}
uint8_t hit_land(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8)
{
#if DEBUG_DISABLE
    debug_line("==============hit_land============");
#endif

    for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix4x4->row, row, col) == 1)
            {
                if((y + row) >= (MATRIX16x8_ROW_MAX - 1))
                {
#if DEBUG_DISABLE
                    debug_int2("hit1 row = %d, col = %d", row, col);
#endif
                    return 1;
                }    

                if(get_matrix_bit(matrix16x8->row, y + row + 1, x + col) == 1)
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
uint8_t is_valid(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8)
{
#if DEBUG_DISABLE
    debug_line("==============is_valid============");
#endif
    for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix4x4->row, row, col) == 1)
            {
                if(get_matrix_bit(matrix16x8->row, y + row, x + col) == 1)
                {
#if DEBUG_DISABLE
                    debug_line("not valid1");
                    debug_int2("row = %d, col = %d", row, col);
#endif
                    return 0;
                }

                if(( x + col < 0) || (x + col >= MATRIX16x8_COLUMN_MAX))
                {
#if DEBUG_DISABLE
                    debug_line("not valid2");
                    debug_int2("row = %d, col = %d", row, col);
#endif
                    return 0;
                }
                if((y + row) > (MATRIX16x8_ROW_MAX - 1))
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
uint8_t is_left_boundary(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8)
{
    for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix4x4->row, row, col) == 1)
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
uint8_t is_right_boundary(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8)
{
    for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix4x4->row, row, col) == 1)
            {
                if(x + col > MATRIX16x8_COLUMN_MAX - 1)
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
uint8_t fall_off(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8)
{
    while(1)
    {
#ifndef WINDOW_BASE
    	Seed++;
#endif

        for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
        {
            for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
            {
                if(get_matrix_bit(matrix4x4->row, row, col) == 1)
                {
                    if(get_matrix_bit(matrix16x8->row, y + row + 1, x + col) == 1)
                    {
#if DEBUG_DISABLE
                        debug_line("fall_off1");
                        debug_int2("x = %d, y = %d", x, y);
#endif
                        return y;
                    }    
                    if((y + row) >= (MATRIX16x8_ROW_MAX - 1))
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
void clear(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, MATRIX16x8* matrix16x8)
{
    for(uint8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix4x4->row, row, col) == 1)
            {
            	set_matrix_bit(matrix16x8->row, y + row, x + col, 0);
            }                             
        }            
    }            
}     
void merge(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, MATRIX16x8* matrix16x8)
{
#if DEBUG_DISABLE
	printf_debug_MATRIX4x4("Before merge MATRIX16x8", x, y, matrix4x4);
	printf_debug_MATRIX16x8("Before merge MATRIX16x8", matrix16x8);
#endif

	for(uint8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
	{
		for(uint8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit(matrix4x4->row, row, col) == 1)
			{
				set_matrix_bit(matrix16x8->row, y + row, x + col, 1);
			}
		}
	}
#if DEBUG_DISABLE
printf_debug_MATRIX16x8("After merge MATRIX16x8", matrix16x8);
#endif
}     
void merge1(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8_in, MATRIX16x8* matrix16x8_out)
{
#ifdef WINDOW_BASE
    size_t len;
#else
    register size_t len;
#endif    
    len = sizeof(MATRIX16x8);
    memcpy(matrix16x8_out, matrix16x8_in, len);

    for(uint8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
        {
            if(get_matrix_bit(matrix4x4->row, row, col) == 1)
            {
				set_matrix_bit(matrix16x8_out->row, y + row, x + col, 1);
            }                             
        }            
    }            
}     

uint16_t get_num_of_orphan(const MATRIX16x8* matrix)
{
    uint16_t risk = 0;
    uint8_t full = 0xFF;
    for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
    {
        full = 0xFF;
        for(int8_t row = MATRIX16x8_ROW_MAX - 1; row >= 0; row--)
        {
            if(full == 0xFF)
            {
                full = get_matrix_bit(matrix->row, row, col);
            }
            else
            {
                if(get_matrix_bit(matrix->row, row, col) == 1)
                {
                    if(full == 0)
                    {
                        risk++;
                    }
                }
                full = get_matrix_bit(matrix->row, row, col);
            }
        }
    }
#if DEBUG_DISABLE
    debug_int1("risk = %d", risk);
#endif

    return risk;
}
uint16_t get_heavy(const MATRIX16x8* matrix)
{
	uint8_t start;
    uint16_t risk = 0;
    uint8_t pre = 0xFF;
    for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
    {
    	pre = 0xFF;
        start = 0;
        for(int8_t row = MATRIX16x8_ROW_MAX - 1; row >= 0; row--)
        {
        	if(pre == 0xFF)
        	{
        		pre = get_matrix_bit(matrix->row, row, col);
        	}
        	else
        	{
                if(pre != get_matrix_bit(matrix->row, row, col))
                {
                	pre = get_matrix_bit(matrix->row, row, col);
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
int8_t left_most(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8)
{
    while(1)
    {
#ifndef WINDOW_BASE
    	Seed++;
#endif

        if(is_left_boundary(x, matrix4x4, matrix16x8) == LEFT_OVER_BOUNDARY)
        {
#if DEBUG_DISABLE
            debug_int1("left_most = %d", x + 1);
#endif
            return x + 1;
        }
        x--;
    } 
}    
int8_t right_most(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX16x8* matrix16x8)
{
    while(1)
    {
#ifndef WINDOW_BASE
    	Seed++;
#endif

        if(is_right_boundary(x, matrix4x4, matrix16x8) == RIGHT_OVER_BOUNDARY)
        {
#if DEBUG_DISABLE
            debug_int1("right_most = %d", x - 1);
#endif
            return x - 1;
        }
        x++;
    } 
}    
uint8_t get_high(MATRIX16x8* matrix)
{
    for(int8_t row = MATRIX16x8_ROW_MAX - 1; row >= 0; row--)
    {
        if(is_row_empty(matrix, row) == 1)
        {
#if DEBUG_DISABLE
            debug_int1("get_high height = %d", MATRIX16x8_ROW_MAX - row - 1);
#endif
            return (uint8_t)(MATRIX16x8_ROW_MAX - row - 1);
        }
    } 
    return MATRIX16x8_ROW_MAX;
}
uint8_t get_high_after_merge(int8_t y, MATRIX4x4* matrix)
{
#if DEBUG_DISABLE
    debug_line("get_high_after_merge");
#endif
    for(int8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
    {
        for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
        {
        	if(get_matrix_bit(matrix->row, row, col) == 1)
        	{
#if DEBUG_DISABLE
                debug_int1("y = %d", y);
                debug_int1("row = %d", row);
                debug_int1("height = %d", MATRIX16x8_ROW_MAX - y - row);
#endif
                return (uint8_t)(MATRIX16x8_ROW_MAX - y - row);
        	}
        }
    }
}
uint8_t get_holes_after_merge(MATRIX16x8* matrix)
{
	int8_t start = -1;
	int8_t stop = -1;
	uint8_t num_hole = 0;
    for(int8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
    {
    	start = stop = -1;
        for(int8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
        {
        	if(col == 0)
        	{
        		if((get_matrix_bit(matrix->row, row, col) == 0) && (get_matrix_bit(matrix->row, row, col + 1) == 1))
        		{
        			if(start == -1)
        			{
            			start = row;
        			}
        		}
        	}
        	else if(col == MATRIX16x8_COLUMN_MAX - 1)
        	{
        		if((get_matrix_bit(matrix->row, row, col) == 0) && (get_matrix_bit(matrix->row, row, col - 1) == 1))
        		{
        			if(start == -1)
        			{
            			start = row;
        			}
        		}
        	}
        	else
        	{
        		if((get_matrix_bit(matrix->row, row, col) == 0) && (get_matrix_bit(matrix->row, row, col - 1) == 1) && (get_matrix_bit(matrix->row, row, col + 1) == 1))
        		{
        			if(start == -1)
        			{
            			start = row;
        			}
        		}
        	}
    		if(start >= 0)
    		{
        		if(row == MATRIX16x8_ROW_MAX - 1)
        		{
        			if(stop == -1)
        			{
            			stop = MATRIX16x8_ROW_MAX;
        			}
        		}
        		else if(get_matrix_bit(matrix->row, row + 1, col) == 1)
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
MATRIX4x4* temp_cur_matrix4x4;
MATRIX16x8 temp_matrix16x8;
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
        temp_cur_matrix4x4 = &g_matrix4x4[g_char_info[g_char_info_index].start_index + tem_sub_index];
        left_most_index = left_most(cur_x, temp_cur_matrix4x4, &g_matrix16x8);
        right_most_index = right_most(cur_x, temp_cur_matrix4x4, &g_matrix16x8);

        for(int8_t temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
        {
            temp_y = fall_off(temp_x, cur_y, temp_cur_matrix4x4, &g_matrix16x8);

#if DEBUG_DISABLE
            printf_debug_MATRIX4x4("After fall off", temp_x, temp_y, temp_cur_matrix4x4);
            printf_debug_Screen("After fall off");
#endif

            if(is_valid(temp_x, temp_y, temp_cur_matrix4x4, &g_matrix16x8) == 0)
            {
                continue;
            }
            res = 1;
            merge1(temp_x, temp_y, temp_cur_matrix4x4, &g_matrix16x8, &temp_matrix16x8);
            temp_high = get_high_after_merge(temp_y, temp_cur_matrix4x4);
            if((get_high(&g_matrix16x8) <= MATRIX16x8_ROW_MAX/2 + 1)
            && (temp_high <= MATRIX16x8_ROW_MAX/2 + 1))
            {
                temp_risk = (((int16_t)get_num_removed_rows(&temp_matrix16x8)) << 10)
                		   - get_num_of_orphan(&temp_matrix16x8)*4
    					   - temp_high*3
    					   - get_holes_after_merge(&temp_matrix16x8)*2
						   - get_heavy(&temp_matrix16x8);
            }
            else
            {
                temp_risk = (((int16_t)get_num_removed_rows(&temp_matrix16x8)) << 10)
                		   - get_num_of_orphan(&temp_matrix16x8)*2
    					   - temp_high*5
    					   - get_holes_after_merge(&temp_matrix16x8)*3
						   - get_heavy(&temp_matrix16x8);
            }
#if DEBUG_DISABLE
            printf_debug_MATRIX16x8("Valid instance", &temp_matrix16x8);
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
        g_char_info_sub_index = tem_pre_sub_index;
        cur_x = temp_pre_x;
#if DEBUG_DISABLE
        printf_debug_cur_MATRIX4x4("Chosen", cur_x, cur_y);
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
void test_is_row_full(const MATRIX16x8* matrix)
{
    for(uint8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_full(matrix, row) == 0 ? "not full" : "full");
    }
}
void test_is_row_empty(const MATRIX16x8* matrix)
{
    for(uint8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_empty(matrix, row) == 0 ? "not empty" : "empty");
    }
}
void test_hit_land()
{
    int8_t x = 5, y = 6;
    MATRIX4x4* matrix4x4 = get_MATRIX4x4(1, 0);
    MATRIX16x8 matrix16x8 =
    {
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
    };
    printf_debug_MATRIX4x4(NULL, x, y, matrix4x4);
    printf_debug_MATRIX16x8(NULL, &matrix16x8);
    hit_land(x, y, matrix4x4, &matrix16x8);
}
void test_is_valid()
{
    int8_t x = 5, y = 7;
    MATRIX4x4* matrix4x4 = get_MATRIX4x4(1, 0);
    MATRIX16x8 matrix16x8 =
    {
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
    };
    printf_debug_MATRIX4x4(NULL, x, y, matrix4x4);
    printf_debug_MATRIX16x8(NULL, &matrix16x8);
    is_valid(x, y, matrix4x4, &matrix16x8);
}
void test_find_best_solution()
{
    g_char_info_index = 1;
    find_best_solution();
}
void test_get_holes_after_merge()
{
    MATRIX16x8 matrix16x8 =
    {
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
    };
    printf_MATRIX16x8(&matrix16x8);
    get_holes_after_merge(&matrix16x8);
}
#endif
#ifndef WINDOW_BASE
void eeprom_write_int(uint8_t at, uint16_t value)
{
    uint8_t temp;
    temp = value >> 8;
    eeprom_write(at, temp);

    temp = value & 0xFF;
    eeprom_write(at + 1, temp);
#if DEBUG_DISABLE
        debug_int1("eeprom_write_int = %d", value);
#endif    
}
uint16_t eeprom_read_int(uint8_t at)
{
    uint16_t value = 0;
    value = eeprom_read(at) << 8;
    value += eeprom_read(at + 1);
#if DEBUG_DISABLE
        debug_int1("eeprom_read_int = %d", value);
#endif
    return value;
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
    max7219_init1(); // initialize  max7219.

    Seed = eeprom_read_int(SEED_EEPROM_INDEX);
	srand(Seed);
#endif
__start:
    Clear_Matrix();
//    printf_debug_all_MATRIX4x4();
//    printf_debug_MATRIX16x8("MATRIX16x8", &g_matrix16x8);
//    goto __exit;
    while(1)
    {
#ifndef WINDOW_BASE
    	Seed++;
		eeprom_write_int(SEED_EEPROM_INDEX, Seed);
#endif

        cur_y = 0;
        cur_x = 2, cur_y = 0;
        g_char_info_index = char_info_index_rand();
        g_char_info_sub_index = 0;

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
        g_cur_matrix4x4 = &g_matrix4x4[g_char_info[g_char_info_index].start_index + g_char_info_sub_index];
#if DEBUG_DISABLE
		printf_debug_MATRIX4x4("MATRIX4x4 chosen", cur_x, cur_y, g_cur_matrix4x4);
#endif

        while(1)
        {
#ifndef WINDOW_BASE
        	Seed++;
#endif

            hit_res = hit_land(cur_x, cur_y, g_cur_matrix4x4, &g_matrix16x8);
#if DEBUG_DISABLE
            debug_int1("hit_res = %d", hit_res);
#endif
            merge(cur_x, cur_y, g_cur_matrix4x4, &g_matrix16x8);
            if(hit_res == 1)
            {
                printf_Screen();
#ifdef WINDOW_BASE
                Sleep(100);
#else
                __delay_ms(100);
#endif
                delete_matrix(&g_matrix16x8);
            }
#if DEBUG_ENABLE
            printf_debug_MATRIX16x8("Main screen", &g_matrix16x8);
#endif
            printf_Screen();
            if(hit_res == 0)
            {
                clear(cur_x, cur_y, g_cur_matrix4x4, &g_matrix16x8);
            }
            else
            {
                break;
            }
#ifdef WINDOW_BASE
            Sleep(500);
#else
            __delay_ms(200);
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
