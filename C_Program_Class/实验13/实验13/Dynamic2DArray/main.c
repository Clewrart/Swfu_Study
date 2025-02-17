#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **p,i,j;
    p=(int **)calloc(3,sizeof(int *));
    for(i=0;i<3;i++)
    {
        p[i]=(int *)calloc(4,sizeof(int));
    }
    printf("动态2d-array元素地址是：\n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            printf("%p ",&p[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<3;i++)
    {
        free(p[i]);
    }
    free(p);
    return 0;
}
