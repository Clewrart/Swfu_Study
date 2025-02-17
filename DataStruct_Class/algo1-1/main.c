#include <stdio.h>

void main()
{
    int i, n;
    float a[20];
    a[0]=1;

    for (i=1;i<=20;i++)
        {
        a[i]=a[i-1]*i*2;
        if((a[i]/i/2)!=(a[i-1]))
            {
                break;//反向验证
            }
        printf("%f    ", a[i]);
        }


}

/* unsigned int f= 1;
        unsigned int p = 1;

        // 计算阶乘
        for (i = 1; i <= n ; i++) {
            f *= i;
            p *= 2;
        }

        if (f * p > INTMAX ) {
            printf("溢出！", n - 1);
            break;
        }
        else{
            a[n] = f * p;
            continue;
        }


    }

    // 输出结果
    printf("结果:\n");
    for (i = 0; i < n; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }

    return 0;
}*/
