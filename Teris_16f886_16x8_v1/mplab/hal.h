#if WINDOW_BASE
#include "hal_window.h"
#else
#include "hal_max7219.h"
#endif

void hal_print_Screen()
{
	hal_print_MATRIX16x8(&g_matrix16x8);
}
