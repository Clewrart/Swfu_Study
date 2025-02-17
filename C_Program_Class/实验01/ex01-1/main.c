//四则运算
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a,b;
    double c; //商存在小数

    printf("请输入两个整数,空格键分开：");

    scanf("%d %d",&a,&b);

    printf("和 %d\n",a + b);

    printf("差 %d\n",a - b);

    printf("积 %d\n",a * b);


    if (b == 0)//除数不能为0
    {
        printf("除数0无法计算商！！！");
    }

    else
    {
        c =1.0 * a / b;

        printf("商 %f\n",c);

    }
    return 0;

}
