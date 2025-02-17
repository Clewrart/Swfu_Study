#include <stdio.h>
#include <stdlib.h>
void reverse(char *p);
int main()
{
    char s[50];
    printf("请输入一个字符串：");
    gets(s);
    printf("输入的字符串是：%s\n", s);
    reverse(s);
    printf("该字符串逆序后：%s\n", s);
    return 0;
}

void reverse(char *p)
{
    int len = strlen(p);//长度
    int i;
    int n = len / 2;
    char cache1;//逆序暂存
    for (i = 0; i <= n; i++)
    {
        cache1 = p[i];
        p[i] = p[len - 1 - i];
        p[len - 1 - i] = cache1;
    }
    return p;
}
