#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double a,b;

    printf("请输入两个数_输入小数,用空格键分开）：");

    scanf("%lf %lf",&a,&b);

    printf("和 %f\n", a + b);

    printf("差 %f\n", a - b);

    printf("积 %f\n", a * b);

    printf("商 %f\n", a / b);

    return 0;

}

