#define WINDOW_BASE 1
#define DEBUG 1

#include "common.h"
#if !(WINDOW_BASE)
#include "usart_pic16.h"
#include "max7219.h"
#endif
#include "debug.h"
#include "array_control.h"
#include "math_control.h"
#include "memory_control.h"
#include "logic.h"
#include "hal.h"

#if (WINDOW_BASE)
#include "unittest.h"
#endif


void main_init()
{
#if !(WINDOW_BASE)
    max7219_init1();
#endif
    dbg_init();
}     

void animate()
{
    while(1)
    {
        hal_print_Main_Screen();
        dbg_print_MATRIX88(1, "Main Screen", &g_matrix88[g_matrix88_index]);        
        DELAY_MS(1000);
        lg_goto_next_character();
    }
}     

void main_close()
{
    dbg_close();
}     
int main()
{
    main_init();
    
//    dbg_print1(1, "value = %d", UINT8_T_ARRAY2(g_matrix88[g_matrix88_index].data, 1, 1));  
//    UINT8_T_ARRAY2(g_matrix88[g_matrix88_index].data, 1, 1) = 0;  
//    dbg_print1(1, "value = %d", UINT8_T_ARRAY2(g_matrix88[g_matrix88_index].data, 1, 1));  
//    int p1[5], p2[6];
//    MEMSET(p1, 0, 24);
    animate();
//    hal_print_Main_Screen();  
//    dbg_print_MATRIX88(1, "Main Screen", &g_matrix88);  
//#if (WINDOW_BASE)
//    ut_testsuite_run();    
//#endif
//    dbg_print1(1, "Running mode %d", WINDOW_BASE);    
    
#if !(WINDOW_BASE)
    while(1);    
#endif
    main_close();
#if (WINDOW_BASE)
    system("PAUSE");
#endif
    return 0;
}
