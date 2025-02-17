#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp1 = fopen("D:/01本科资料/2023-2024-01-C语言-赵毅力/实验12/实验12/FileDemo01/weekdays.txt","r");
    FILE *fp2 = fopen("file.txt","w");

    char c;

    while ((c = fgetc(fp1)) != EOF)
        {
            fputc(c,fp2);
        }

    fclose(fp1);
    fclose(fp2);
return 0;
}
