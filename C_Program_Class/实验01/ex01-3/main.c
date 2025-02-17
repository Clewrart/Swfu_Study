#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int s,c,r ;

    const double P = 3.1415926;

    printf("请输入圆的半径整数cm：");

    scanf("%d",&r);

    s = P * r * r;

    c = P * 2 * r;

    printf("圆的面积(取整）为：%d cm2\n",s);

    printf("圆的周长(取整）为：%d cm\n",c);

    return 0;
}
