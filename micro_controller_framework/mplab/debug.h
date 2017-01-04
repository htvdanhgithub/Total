#if (WINDOW_BASE)
#include "debug_window.h"
#else
#include "debug_uart.h"
#endif

void dbg_print_MATRIX88(uint8_t enable, const char* lable, const MATRIX88* matrix)
{
    if((DEBUG) && (enable))
    {    
        if(lable != NULL)
        {
            dbg_print(enable, lable);
            dbg_print_line(enable, ":");
        }
        dbg_print_line(enable, "<<<<<<<<<<<<<<<<<<<<MATRIX88");
        for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
        {
            for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
            {
                if(matrix->data[row][col] == 1)
                {
                    dbg_print(enable, "*");
                }
                else
                {
                    dbg_print(enable, "_");
                }
            }
            dbg_print_line(enable, "");
        }
        dbg_print_line(enable, ">>>>>>>>>>>>>>>>>>>>");
    }
}
