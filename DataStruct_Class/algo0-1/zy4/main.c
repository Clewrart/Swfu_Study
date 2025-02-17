/* main2-1.c 检验bo2-1.c的主程序 */
#include "c1.h"
#include "c2-1.h"
#include <stdio.h>

int main() {
    SqList L;
    ElemType e, a[5] = {'a', 'b', 'c', 'd', 'e'};
    int i, j;

    printf("初始化L前：L.elem=%p L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);

    /*(1) 初始化顺序表L；*/
    i = InitList(&L);
    printf("1.初始化L后：L.elem=%p L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);

    /*(2)依次采用尾插法插入’a’,’b’,’c’,’d’,’e’元素；*/
    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, j, a[j - 1]);

    /*(3)输出顺序表L；*/
    printf("2-3.顺序表L的元素为：");
    for (i = 0; i < L.length; i++)
        printf("%c ", L.elem[i]);
    printf("\n");

    /*(4)输出顺序表L长度；*/
    printf("4.顺序表L的长度为：%d\n", ListLength(L));

    /*(5)输出顺序表L的第3个元素；*/
    GetElem(L, 3, &e);
    printf("5.顺序表L的第3个元素为：%c\n", e);

    /*(6)在第4个元素位置上插入’f’元素；*/
    ListInsert(&L, 4, 'f');

    /*(7)输出顺序表L；*/
    printf("6-7.插入元素后，顺序表L的元素为：");
    for (i = 0; i < L.length; i++)
        printf("%c ", L.elem[i]);
    printf("\n");

    /*(8)删除L的第3个元素；*/
    ListDelete(&L, 3, &e);

    /*(9)输出顺序表L；*/
    printf("8-9.删除元素后，顺序表L的元素为：");
    for (i = 0; i < L.length; i++)
        printf("%c ", L.elem[i]);
    printf("\n");

    /*(10)释放顺序表L。*/
    DestroyList(&L);
    printf("10.释放后：%c |", L);

    return (1);
}
