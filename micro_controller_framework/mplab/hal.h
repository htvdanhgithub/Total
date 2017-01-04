#if (WINDOW_BASE)
#include "hal_window.h"
#else
#include "hal_max7219.h"
#endif

void hal_print_Main_Screen()
{
    hal_print_MATRIX88(&g_matrix88[g_matrix88_index]);     
}     
