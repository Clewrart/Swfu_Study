#include <stdio.h>
#include <stdlib.h>

#define N 10

void get_max_min(int *p, int n, int *maxi, int *mini);

int main()
{
    int ws[N] = { 20, 19, 92, 50, 59, 18, 76, 84, 31, 65 };

    int maxi = ws[0];
    int mini = ws[0];

    get_max_min(ws, N, &maxi, &mini);

    printf("数组中的最大元素maxi = %d\n", maxi);
    printf("数组中的最小元素mini = %d\n", mini);

    return 0;
}

void get_max_min(int *p, int n, int *maxi, int *mini)
{

    for(int i = 0;i<n; i++)
    {

        if (*maxi< *(p+i))
        {
            *maxi = *(p+i);

        }
    }

    for(int i = 0;i<n;i++)
    {
        if(*mini> *(p+i))
        {
           *mini = *(p+i);
        }
    }
    return 0;
}
