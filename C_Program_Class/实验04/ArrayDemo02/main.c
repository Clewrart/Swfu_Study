#include <stdio.h>
#include <stdlib.h>

#define N 10

void array_print(int* arr, int n);

int main()
{
    int arr[N] = { 85, 92, 78, 66, 95, 70, 80, 82, 56, 88 };

    printf("数组arr：");
    array_print(arr, N);

    int mini = 0;

    for(int q = 0;q < N ; q++)
    {
        if(arr[q+1] > arr[q])
        {
            mini=arr[q];

        }
    }

    printf("数组最小元素mini = %d\n", mini);

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
