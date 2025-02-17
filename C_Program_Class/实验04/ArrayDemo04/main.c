#include <stdio.h>
#include <stdlib.h>

#define N 10

void array_print(int* arr, int n);

int main()
{
    int arr[N] = { 85, 92, 78, 66, 95, 70, 80, 82, 56, 88 };

    printf("数组arr排序前：");
    array_print(arr, N);
    int linshi;//临时存储

   for ( int p = 0 ; p<N-1 ; p++)
    {
        for (int j = 0;j < N - 1 - p ;j++)
        {
            if(arr[j]>arr[j+1])
            {
                linshi=arr[j];

                arr[j]=arr[j+1];

                arr[j+1]=linshi;
            }
        }
    }

    printf("数组arr排序后：");
    array_print(arr, N);

    return 0;
}

/**
 * 输出数组 arr 的每一个元素
 */
void array_print(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
