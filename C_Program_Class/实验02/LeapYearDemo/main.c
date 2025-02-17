#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    int year;  // 保存用户输入年份的整形变量
    bool isLeapYear = true;  // 判别用户输入年份是否是闰年的布尔类型变量

    printf("请输入一个年份：\n");
    scanf("%d", &year);

    if((year % 100 != 0)&&(year % 4 == 0) || (year % 400 == 0)) //四年一闰+百年不闰，四百再闰
    {
        isLeapYear = 1;//布尔是=1，布尔否=0
    }
    else
    {
        isLeapYear = 0;
    }

    if (isLeapYear)
    {
        printf("%d是闰年！\n", year);
    }
    else
    {
        printf("%d不是闰年！\n", year);
    }

    return 0;
}
