typedef struct 
{
    uint8_t  col[MATRIX88_COLUMN_MAX];
} MATRIX7219;

void hal_MATRIX88_to_MATRIX7219(const MATRIX88* matrix88, MATRIX7219* matrix7219)
{
    uint8_t mask = 0x80;

    for(uint8_t col = 0; col < MATRIX88_ROW_MAX; col++)
    {
        mask = 0x80;
        UINT8_T_ARRAY1(matrix7219->col, col) = 0;
        for(uint8_t row = 0; row < MATRIX88_COLUMN_MAX; row++)
        {
            if(UINT8_T_ARRAY2(((MATRIX88*)matrix88)->data, row, col) == 1)
            {
                UINT8_T_ARRAY1(matrix7219->col, col) |= mask;
            }
            mask >>= 1;
        }
    }
}
void hal_print_MATRIX7219(const MATRIX7219* matrix7219)
{
    uint8_t col;

    for (col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        Write_Byte(col + 1, UINT8_T_ARRAY1(col));
    }
}
void hal_print_MATRIX88(const MATRIX88* matrix88)
{
    MATRIX7219 matrix7219;
    hal_MATRIX88_to_MATRIX7219(matrix88, &matrix7219);
    hal_print_MATRIX7219(&matrix7219);
}
