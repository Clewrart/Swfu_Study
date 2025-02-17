#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x;
    int y;
    int maxi;

    printf("请输入两个整数（用逗号分隔）：");
    scanf("%d,%d", &x, &y);


    if( x > y )
    {
        maxi = x;
    }

    else
    {
        maxi = y;
    }

    printf("%d和%d之间较大的元素是%d\n", x, y, maxi);

    return 0;
}
