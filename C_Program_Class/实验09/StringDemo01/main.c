#include <stdio.h>
#include <stdlib.h>
#define N 50

int front_star_number(const char *p);

int back_star_number(const char *p);

int main()
{
    char s[50];
    printf("请输入一个字符串：");
    gets(s);
    printf("输入的字符串是：%s\n", s);

    int n = front_star_number(s);
    printf("该字符串前星号数目：%d\n", n);

    int m = back_star_number(s);
    printf("该字符串后星号数目：%d\n", m);

    return 0;
}

int front_star_number(const char *p)
{
    int n=0;
   while (*p == '*')
    {
        p++;
        n++;
    }

    return n;
}

int back_star_number(const char *p)
{
    int m=0;
    while (*p != '\0')
    {
        p++;
    }
    p--;

    while (*p == '*')
    {
        p--;
        m++;
    }

    return m;
}
