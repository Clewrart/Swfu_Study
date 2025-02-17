#include <stdio.h>
#include <stdlib.h>
#define N 5
int *findMax(int *p1);
void swap(int *pa_max,int * pb_max);
void output(int *pa,int *pb);
int main()
{
    int a[N]={3,5,2,9,7},b[N]={4,8,6,10,1};
    int *max_a,*max_b;
    printf("【交换前】\n");
    output(a,b);
    max_a=findMax(a);
    max_b=findMax(b);
    swap(max_a,max_b);
    printf("\n【交换后】\n");
    output(a,b);
    return 0;
}
int * findMax(int * p1)
{
    int * max,* p2;
    max=p1;
    for(p2=p1+1;p2<p1+N;p2++)
    {
        if(*p2>*max)
           {
               max=p2;
           }
    }
    return max;
}
void swap(int *pa_max,int *pb_max)
{
    int t;
    t=*pa_max; *pa_max=*pb_max; *pb_max=t;
}
void output(int *pa,int *pb)
{
    int i;
    printf("数组a:");
    for(i=0;i<N;i++)
    {
        printf("%-6d",pa[i]);
    }
    printf("数组b:");
    for (i=0;i<N;i++)
    {
        printf("%-6d",pb[i]);
    }
}

