void hal_MATRIX16x8_to_MATRIX7219(const MATRIX16x8* matrix16x8, MATRIX7219* matrix7219)
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
void hal_print_MATRIX7219(const MATRIX7219* matrix7219)
{
    uint8_t col;

    for (col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
    {
        Write_Word(col + 1, matrix7219->col1[col], col + 1, matrix7219->col2[col]);
    }
}
void hal_print_MATRIX16x8(const MATRIX16x8* matrix88)
{
    MATRIX7219 matrix7219;
    hal_MATRIX16x8_to_MATRIX7219(matrix88, &matrix7219);
    hal_print_MATRIX7219(&matrix7219);
}
