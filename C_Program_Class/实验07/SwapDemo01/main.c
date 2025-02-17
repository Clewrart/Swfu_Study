#include <stdio.h>
#include <stdlib.h>

void swap(double *x, double *y);

int main()
{
    double w1, w2;
    printf("请输入两个小数（用逗号分割）：");
    scanf("%lf,%lf", &w1, &w2);
    printf("交换前：w1 = %lf, w2 = %lf\n", w1, w2);

    swap(&w1,&w2);

    printf("交换后：w1 = %lf, w2 = %lf\n", w1, w2);

    return 0;
}

/**
 * 交换变量x和y的值
 */
void swap(double *x, double *y)
{
    double temp = *x;
    *x = *y;
    *y = temp;
}
