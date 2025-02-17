#include <stdio.h>
#include <stdlib.h>
int fib(x);
int main()
{
    int i;
    printf("斐波那契数列前20项：\n");
      for(i=1;i<=20;i++)
      {
       printf("%d\t",fib(i));
        if(i%10==0)
            printf("\n");
      }
    return 0;
}

int fib(x)
{
    if( x==1||x==2 )
    {
       return (1);
    }
    else
    {
       return (fib(x-1)+fib(x-2));
    }

}
