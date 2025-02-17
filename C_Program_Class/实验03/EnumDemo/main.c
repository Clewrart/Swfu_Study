#include <stdio.h>
#include <stdlib.h>

// 定义星期枚举类型
enum WeekDay
{
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

int main()
{

    enum WeekDay day = FRIDAY;
    switch(day)
    {
        case MONDAY: printf("星期一"); break;
        case TUESDAY: printf("星期二"); break;
        case WEDNESDAY:  printf("星期三"); break;
        case THURSDAY:  printf("星期四"); break;
        case FRIDAY:  printf("星期五"); break;
        case SATURDAY: printf("星期六"); break;
        case SUNDAY:  printf("星期日"); break;
        default: printf("错误！");

    }

    return 0;
}
