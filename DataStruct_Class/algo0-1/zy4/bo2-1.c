/* bo2-1.c 顺序表示的线性表(存储结构由c2-1.h定义)的基本操作(12个) */

#include "c1.h"
#include "c2-1.h"
#include <stdlib.h>

/* 初始化顺序表L */
Status InitList(SqList *L) {
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;
    return OK;
}

/* 销毁顺序表L */
Status DestroyList(SqList *L) {
    free((*L).elem);
    (*L).elem = NULL;
    (*L).length = 0;
    (*L).listsize = 0;
    return OK;
}

/* 清空顺序表L */
Status ClearList(SqList *L) {
    (*L).length = 0;
    return OK;
}

/* 判断顺序表L是否为空 */
Status ListEmpty(SqList L) {
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

/* 返回顺序表L的长度 */
int ListLength(SqList L) {
    return L.length;
}

/* 获取顺序表L中第i个元素的值 */
Status GetElem(SqList L, int i, ElemType *e) {
    if (i < 1 || i > L.length)
        exit(ERROR);
    *e = *(L.elem + i - 1);
    return OK;
}

/* 查找顺序表L中元素e的位置 */
int LocateElem(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)) {
    ElemType *p;
    int i = 1;
    p = L.elem;
    while (i <= L.length && !compare(*p++, e))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

/* 返回cur_e的前驱元素pre_e */
Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e) {
    int i = 2;
    ElemType *p = L.elem + 1;
    while (i <= L.length && *p != cur_e) {
        p++;
        i++;
    }
    if (i > L.length)
        return INFEASIBLE;
    else {
        *pre_e = *--p;
        return OK;
    }
}

/* 返回cur_e的后继元素next_e */
Status NextElem(SqList L, ElemType cur_e, ElemType *next_e) {
    int i = 1;
    ElemType *p = L.elem;
    while (i < L.length && *p != cur_e) {
        i++;
        p++;
    }
    if (i == L.length)
        return INFEASIBLE;
    else {
        *next_e = *++p;
        return OK;
    }
}

/* 在顺序表L的第i个位置插入元素e */
Status ListInsert(SqList *L, int i, ElemType e) {
    ElemType *newbase, *q, *p;
    if (i < 1 || i > (*L).length + 1)
        return ERROR;
    if ((*L).length >= (*L).listsize) {
        newbase = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        (*L).elem = newbase;
        (*L).listsize += LISTINCREMENT;
    }
    q = (*L).elem + i - 1;
    for (p = (*L).elem + (*L).length - 1; p >= q; --p)
        *(p + 1) = *p;
    *q = e;
    ++(*L).length;
    return OK;
}

/* 删除顺序表L的第i个元素，并用e返回其值 */
Status ListDelete(SqList *L, int i, ElemType *e) {
    ElemType *p, *q;
    if (i < 1 || i > (*L).length)
        return ERROR;
    p = (*L).elem + i - 1;
    *e = *p;
    q = (*L).elem + (*L).length - 1;
    for (++p; p <= q; ++p)
        *(p - 1) = *p;
    (*L).length--;
    return OK;
}

/* 对顺序表L的每个元素依次调用函数vi() */
Status ListTraverse(SqList L, void (*vi)(ElemType *)) {
    ElemType *p;
    int i;
    p = L.elem;
    for (i = 1; i <= L.length; i++)
        vi(p++);
    printf("\n");
    return OK;
}
