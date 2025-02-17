#include <stdio.h>
#include <stdlib.h>
int fac(int t);
int Cmn(int m,int n);
int main()
{
    int m,n,t;
    printf("请输入m和n的值：\n");
    scanf("%d %d",&m,&n);
    t=Cmn(m,n);
    printf("组合数Cmn=%d\n",t);
    return 0;
}

int fac(int t)
{
    int i,f=1;
    for(i=1;i<=t;i++)
        {
            f*=i;
        }
    return f;
}
int Cmn(int m,int n)
{
    int C;
    C=fac(m)/fac(n)*fac(m-n);
    return C;
}
