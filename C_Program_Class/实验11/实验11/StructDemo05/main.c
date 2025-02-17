#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct
{
    char num[10];
    int score;
}STU;

STU *find(STU *p) //返回值是结构体指针（规范写法，方便调用）
{
    int i,max,n = 0;
    max = p[0].score;
    for(i = 0;i < N;i++)
    {
        if(p[i].score > max)
        {
            max = p[i].score;
            n = i;
        }
    }
    return &p[n];
}

int main()
{    STU x[N] = {{"GA001",85},{"GA002",76},{"GA003",72},{"GA004",69},{"GA005",88},{"GA006",66},{"GA007",99},{"GA008",77},{"GA009",65},{"GA010",91}};
    STU * top;
    top = find(x);
    printf("最高分学生：\n");
    printf("学号：%s  成绩：%d\n",top->num,top->score);
    return 0;
}

