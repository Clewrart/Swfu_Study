#include <stdio.h>
#include <stdlib.h>

int main()
{
    // 使用for循环实现计算100+98+96+…+2的功能（请从100开始递减）
    int sum = 0;
    int p = 100;
    for( ; ; )
    {
        if(p>0)
        {
            sum = sum + p;
            p = p - 2;
        }
        else
        {
            break;
        }
    }
    printf("sum = %d\n", sum);
    return 0;
}
