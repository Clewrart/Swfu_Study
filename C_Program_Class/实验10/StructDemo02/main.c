#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char num[10];
    char name[10];
    char gender;
    int score[4];
    float aver;

}STU;

int main()
{
    STU x, *p = &x;
    printf("请输入一名学生的信息(学号、姓名、性别、四门课成绩):\n");
    scanf("%s %s %c %d %d %d %d",x.num,x.name,&x.gender,&x.score[0],&x.score[1],&x.score[2],&x.score[3]);
    p->aver = (p->score[0]+p->score[1]+p->score[2]+p->score[3])/4.0;
    printf("\n该学生的平均成绩:%.1f\n",(*p).aver);

    return 0;
}
