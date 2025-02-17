#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year,month,day;
}DATE;

typedef struct
{
    char num[10],name[10],gender;
    DATE birthday;
    int score[4];
}STU;
int main()
{
    STU x={"151101","周晓",'M',{2004,06,18},{82,81,75,86}};
    printf("学号：%s\n",x.num);
    printf("姓名：%s\n",x.name);
    printf("性别：%c\n",x.gender);
    printf("出生日期：%d - %d - %d\n",x.birthday.year,x.birthday.month,x.birthday.day);
    printf("高数：%d, 英语：%d, 政治：%d, C语言：%d",x.score[0],x.score[1],x.score[2],x.score[3]);
    return 0;
}

