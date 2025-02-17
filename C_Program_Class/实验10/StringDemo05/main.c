#include <stdio.h>
#include <stdlib.h>
void mystrcpy(char *s1, char *s2);
int main()
{
    char a[100];
    printf("请输入原始字符串(空格结束，回车执行）:");
    scanf("%s",a);
	char b[100];

	mystrcpy(b,a);
	printf("复制后的字符串为%s\n",b);
	return 0;
}
void mystrcpy(char *s1, char *s2)
{
    while(*s2 != '\0') {
            *s1 = *s2;
            *s1++;
            *s2++;
        }
        *s1 = '\0';
}
