#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // 一元二次方程的三条边
    double a, b, c;
    // 一元二次方程的判别式
    double delta;
    // 一元二次方程的两个实根
    double x1 = 0, x2 = 0;

    printf("请输入三个小数： ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3)
    {
        printf("输入错误！\n");
        return EXIT_FAILURE;
    }

    delta = b * b - 4 * a * c;

    x1=(-b+delta)/(2*a);
    x2=(-b-delta)/(2*a);
    /***********************************************
     * 实验内容：根据判别式计算一元二次方程的根
     **********************************************/



    if (delta > 0)
    {
        printf("方程存在两个不同的实根.\n");

        printf("x1 = %lf, x2 = %lf\n", x1, x2);
    } else if (delta == 0)
    {
        printf("方程存在两个相同的实根.\n");

        printf("x1 = %lf, x2 = %lf\n", x1, x2);
    } else
    {
        printf("方程没有实根.\n");
    }

    return 0;
}
