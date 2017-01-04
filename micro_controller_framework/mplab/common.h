#if (WINDOW_BASE)
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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "myutils.h"
#endif

#define OK 1
#define NG 0

#define YES 1
#define NO 0

#define TRUE 1
#define FALSE 0

#define MATRIX88_COLUMN_MAX 8
#define MATRIX88_ROW_MAX 8

typedef struct 
{
    uint8_t  data[MATRIX88_ROW_MAX][MATRIX88_COLUMN_MAX];
} MATRIX88;

#if (WINDOW_BASE)
#define DELAY_MS(x) Sleep(x)
#else
#define DELAY_MS(x) __delay_ms(x)
#endif

#if(DEBUG)        
#define UINT8_T_ARRAY1(array, x) ARRAY1(uint8_t, array, x)
#define UINT8_T_ARRAY2(array, x, y) ARRAY2(uint8_t, array, x, y)
#else
#define UINT8_T_ARRAY1(array, x) array[x]
#define UINT8_T_ARRAY2(array, x, y) array[x][y]
#endif
