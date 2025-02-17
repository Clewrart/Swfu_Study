#include <stdio.h>
#include <stdlib.h>
int main(){
    int my_max(int x,int y);
    int x1;
    int x2;
    printf("请输入两个整数：");
    scanf("%d %d",&x1,&x2);
    int max = my_max(x1,x2);
    printf("max=%d\n",max);
    return 0;

}


int my_max(int x,int y)
{
    int maxi;
    if(x>y)
    {
        maxi=x;
    }
    else
    {
        maxi=y;
    }
    return(maxi);
}
