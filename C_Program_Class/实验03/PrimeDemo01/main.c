#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int n;
    int i;
    printf("请输入一个整数：");
    scanf("%d", &n);

    bool isPrime = true;

    // 使用for循环实现判别整数n是否是素数的功能

    if(n == 1)
        {
            printf("素数不包括1\n");
        }
        else
        {
            for(i=2; i<n; i++)
            {
                if (n%i==0)
                {
                    isPrime = false;
                    break;
                }
            }
        }

    if (isPrime&&n!=1)
    {
        printf("%d是素数！\n", n);
    }
    else
    {
        printf("%ds不是素数！\n", n);
    }

    return 0;
}
