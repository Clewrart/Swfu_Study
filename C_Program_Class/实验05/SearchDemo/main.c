#include <stdio.h>
#include <stdlib.h>

#define N 10

// 函数的原型声明
int my_linear_search(int* arr, int n, int key);
int my_binary_search(int* arr, int n, int key);

int main()
{
    int scores[N] = { 57, 62, 67, 73, 76, 79, 81, 85, 90, 93 };
    int key = 90;
    int pos;

    printf("使用线性查找算法，查找元素%d：", key);
    pos = my_linear_search(scores, N, key);
    printf("位于%d。\n", pos);

    printf("使用二分查找算法，查找元素%d：", key);
    pos = my_binary_search(scores, N, key);
    printf("位于%d。\n", pos);


    key = 89;
    printf("使用线性查找算法，查找元素%d：", key);
    pos = my_linear_search(scores, N, key);
    printf("位于%d。\n", pos);

    printf("使用二分查找算法，查找元素%d：", key);
    pos = my_binary_search(scores, N, key);
    printf("位于%d。\n", pos);
    return 0;
}

/**
 * 实现线性查找算法
 */
int my_linear_search(int* arr, int n, int key)
{
    int index = -1;
    int l = 0;
    int h = n-1;
    for (int i = 0; i < n; i++)
        {
            if (arr[i]==key)
            {
                index = i;
            }
        }

    return index;


}

/**
 * 实现二分查找算法
 */
int my_binary_search(int* arr, int n, int key)
{
    int index = -1;
      int l2 = 0;
    int m2;
    int h2 = n-1;
    while(l2 <= h2)
    {
        m2 = (l2+h2)/2;
        if(arr[m2] == key){
            index = m2;
            break;
        }
        else if(key > arr[m2]){
            l2 = m2+1;

        }
        else if(key < arr[m2]){
            h2 = m2-1;

        }
    }

    return index;
}
