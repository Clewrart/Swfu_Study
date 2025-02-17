#include <stdio.h>
#include <stdlib.h>
#include <math.h>//fabs()用

int main()
{
    double n = 1.0;       // 通项的分母
    double sign = 1.0;    // 通项的符号位
    double t = 1.0;       // 通项
    double sum = 0.0;     // 累加和

    while(fabs(t)>(1e-6)) //fabs（x）求x绝对值abs,大于要循环，所以用大于号
    {
        sum +=t;
        n = n+2;
        sign= sign *(-1);
        t = sign/n;
    }

    printf("圆周率的近似值=%lf\n", 4.0 * sum);

    return 0;
}
