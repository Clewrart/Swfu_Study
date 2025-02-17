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
    STU *p = x;
    int i ;
    printf("%-10s%-10s%-8s%-8s%-8s%s\n","学号","姓名","高数","英语","政治","平均成绩");
    for(i = 0;i < 4;i++)
    {
        (p + i)->avg = ((p + i)->score[0] + (p + i)->score[1] + (p + i)->score[2]) / 3.0;
        printf("%-10s%-10s%-8d%-8d%-8d%.1f\n",(p + i)->num,(p + i)->name,(p + i)->score[0],(p + i)->score[1],(p + i)->score[2],(p + i)->avg);
    }
    return 0;
}

