#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x;
    int y;
    int z;
    int maxi;

    printf("请输入三个整数（用逗号分隔）：");
    scanf("%d,%d,%d", &x, &y, &z);

    if (x > y && x > z)//筛选x ： x必大于yz
    {
        maxi = x ;
    }

    else if  (z > y)//筛选z:z必大于y；如果x大，之前已选走，不再执行本步骤
    {
        maxi = z ;
    }

    else
    {
        maxi = y ;
    }


    printf("%d，%d和%d之间较大的元素是%d\n", x, y, z, maxi);

    return 0;
}
