#include <stdio.h>
#include <stdlib.h>

int main()
{
    // 使用for循环实现计算1+2+3+…+100的功能
    int sum = 0;
    int p;//循环控制步骤变量


   for(p=1;p<=100;p++)
   {
        sum = sum + p;
    }

    printf("sum = %d\n", sum);
    return 0;
}
