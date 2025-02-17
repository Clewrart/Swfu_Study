#include <stdio.h>
#include <stdlib.h>
int *findmax(int*p)
{
    int i,*pmax;
    pmax=p;
    for(i=1;i<10;i++)
    {
        if(*(p+i) > *pmax)
        {
            pmax = p + i;
        }
    }
    return pmax;
}


int main()
{
    int a[10] = {5,9,2,4,10,8,1,7,6,3},i,*max;
    for(i = 0; i<10;i++)
    {
        printf("%-4d",a[i]);
    }
    max = findmax(a);
    printf("\n最大值为：%d\n",*max);
    return 0;
}
