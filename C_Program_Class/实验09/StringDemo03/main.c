#include <stdio.h>
#include <stdlib.h>
void find_longest(char str[]);
int main()
{
    char s[50];
    printf("请输入一个字符串：");
    gets(s);
    printf("输入的字符串是：%s\n", s);
    void findLongest(char str[]);
    findLongest(s);
    return 0;
}

void findLongest(char str[])
{
    int len1=0;//检查的单词长度
    int lenm=0;//检查到的单词最长长度
    int start1=0;//分词单词
    int MaxWord=0;//最长单词

    int i=0;
    int j=0;

    for(i=0;str[i];i++)
    {
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
        {
            if(len1==0)//当前长度等于0时，查找完
                start1=i;//新单词的开始位置
            len1++;
        }
        if(len1>lenm)//dangqian单词的长度大于最大值
        {
            lenm = len1;
            MaxWord = start1;
        }
        if(str[i]==' ')//遇到空格结束
        {
            len1 = 0;
        }
    }

    printf("最长单词");
     for(j=MaxWord;j <MaxWord+lenm;j++)
    {
        char uu =str[j];
        printf("%c",uu);

    }
    printf("\n最长单词字母数 %d",lenm);
}


