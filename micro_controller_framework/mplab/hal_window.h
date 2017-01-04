void hal_print_MATRIX88(const MATRIX88* matrix88)
{
    printf("<<<<<<<<<<<<<<<<<<<<MATRIX88\n");
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(UINT8_T_ARRAY2(((MATRIX88*)matrix88)->data, row, col) == 1)
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
}
