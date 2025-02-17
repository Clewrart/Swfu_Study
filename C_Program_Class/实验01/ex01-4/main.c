#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    printf("输入三个边长，空格分割:");

    double a,b,c,H;

    scanf("%lf%lf%lf",&a,&b,&c);


    H = sqrt((a+b+c)/2 * ((a+b+c)/2-a) * ((a+b+c)/2-b) * ((a+b+c)/2-c));

    printf("面积是%0.2f \n注意！如果为0则三角形不存在！",H);

    return 0;
}
