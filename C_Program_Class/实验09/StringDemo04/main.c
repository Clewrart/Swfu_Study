#include <stdio.h>
#include <stdlib.h>

int mystrlen(const char *p);

int main()
{
    char s[50];
    printf("请输入一个字符串：");
    gets(s);
    printf("输入的字符串是：%s\n", s);

    int n = mystrlen(s);
    printf("该字符串长度为：%d\n", n);

    return 0;
}

int mystrlen(const char *p)

{
    int sslen = strlen(p);

    return sslen;
}

