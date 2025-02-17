#include <stdio.h>
#include <stdlib.h>

void output(int*p);
void sort(int p[ ]);
int main()
{
    int a[10]={2,4,9,1,5,8,10,7,6,3};
    printf("数组初始值：\n");
    output(a);
    sort(&a[4]);
    printf("\n 排序后6位结果\n");
    output(a);
    return 0;
}
void output(int*p)
{
    int i;
    for(i = 0;i<10;i++)
    {
        printf("%-6d",*(p+i));
    }
}
void sort(int p[ ])
{
    int i,j,t;
    for (i = 0;i<5;i++)
    {
        for(j=0;j<5-i;j++)
        {
            if(p[j]<p[j+1])
            {
                t =p[j];
                p[j]= p[j+1];
                p[j+1] = t;
            }
        }
    }
}
