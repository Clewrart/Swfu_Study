#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 4

void array2d_print(int (*p)[COLS], int n);
void get_max_min(int (*p)[COLS], int n, int *maxi, int *mini);

int main()
{
    int mat[ROWS][COLS] = {
        { 73, 86, 85, 76 },
        { 92, 66, 94, 75 },
        { 80, 74, 68, 70 }
    };

    printf("二维数组：\n");
    array2d_print(mat, ROWS);

    int maxi, mini;
    get_max_min(mat, ROWS, &maxi, &mini);

    printf("二维数组的最大值：%d\n", maxi);
    printf("二维数组的最小值：%d\n", mini);


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

void get_max_min(int (*p)[COLS], int n, int *maxi, int *mini)
{
    *maxi = p[0][0];
    *mini = p[0][0];




    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<4;j++)
        {
            if(*mini > p[i][j])
            {
                *mini = p[i][j];
            }

            if ( *maxi< p[i][j] )
            {
                *maxi = p[i][j];
            }
        }
    }
    return 0;
}
