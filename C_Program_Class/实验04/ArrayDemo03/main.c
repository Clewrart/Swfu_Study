#include <stdio.h>
#include <stdlib.h>

#define N 20

void array_print(int* arr, int n);

int main()
{
    int fib[N];
	int p;

    fib[0]=1;//此数列第一项，第二项为1，及下标0和下标1的项为1
    fib[1]=1;

	for(p=2 ; p<=N ; p++)
	{
		fib[p] = fib[p-1] + fib[p-2];
	}



    printf("斐波那契数列前%d项：", N);
    array_print(fib, N);

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
