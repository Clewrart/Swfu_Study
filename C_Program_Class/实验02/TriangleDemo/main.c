#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(void)
{
    double x1,x2,x3;
    double s;//保存海伦公式 二分之边长和  值
    double a; // 保存三角形的面积
    bool isTriangle = true;  // 判断三条边是否构成三角形的布尔类型变量


    printf("请输入三角形的三条边：\n");
    scanf("%lf%lf%lf", &x1, &x2, &x3);

    s = x1/2+x2/2+x3/2;
    a = sqrt((s) * ((s)-x1) * ((s)-x2) * ((s)-x3));
    isTriangle = x1+x2>x3 && x1+x3>x2 && x2+x3>x1 ;

    if (isTriangle)
    {
        printf("面积是%0.2f \n",s);
    }
    else
    {
        printf("请检查！不能组成三角形！");
    }


    return 0;

}
