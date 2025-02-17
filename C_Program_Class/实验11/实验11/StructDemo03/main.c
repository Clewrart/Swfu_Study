#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    char num[10];
    char name[10];
    int score[3];
    float avg;
}STU;


int main()
{
    STU x[4] = {{"001","周晓",{99,89,77}},{"002","伊凡",{99,97,99}},{"003","张三",{56,94,78}},{"004","李四",{77,88,66}}};
    int i;
    printf("%-10s%-10s%-8s%-8s%-8s%s\n","学号","姓名","高数","英语","政治","平均成绩");
    for(i = 0;i < 4;i++)
    {
        x[i].avg = (x[i].score[0] + x[i].score[1] + x[i].score[2]) / 3.0;
        printf("%-10s%-10s%-8d%-8d%-8d%.1f\n",x[i].num,x[i].name,x[i].score[0],x[i].score[1],x[i].score[2],x[i].avg);
    }
    return 0;
}




