#include <stdio.h>
#include <stdlib.h>

#define N 7

int main()
{
    char *weekdays[N];

    FILE *fp=fopen("D:/01本科资料/2023-2024-01-C语言-赵毅力/实验12/实验12/FileDemo01/weekdays.txt","r");


    if(fp!=NULL)
        {
            while(fgets(weekdays,N,fp))
            {
                printf("%s",weekdays);
            }
        }
    fclose(fp);

    return 0;
}
