#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3

void array2d_print(int (*p)[COLS], int n);
void diag(int (*p)[COLS], int n);

int main()
{
    int mat[ROWS][COLS] = {
        { 73, 86, 85 },
        { 92, 66, 94 },
        { 80, 74, 68 }
    };

    printf("原始二维数组：\n");
    array2d_print(mat, ROWS);

    diag(mat, ROWS);
    printf("处理后的二维数组：\n");
    array2d_print(mat, ROWS);


    return 0;
}

void array2d_print(int (*p)[COLS], int n)
{
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            printf("%d ", p[r][c]);
        }
        printf("\n");
    }
}

void diag(int (*p)[COLS], int n)
{
    for (int i = 0;i < ROWS;i++)
    {
        for (int a = 0;a < COLS;a++)
        {
            if ( i >= a)
            {
                p[i][a]=0;
            }
            printf("\n ");
        }
    }
}

