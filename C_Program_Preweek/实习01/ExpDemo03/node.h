#ifndef NODE_H
#define NODE_H

typedef struct node
{
    int data;
    struct node *next;
} NODE;

// 创建链表
NODE* createList(int* a, int n);

// 输出链表元素
void outputList(NODE* head);

// 删除链表
void deleteList(NODE* head);

// 添加结点
void insertNode(NODE* head, int data);

// 删除结点
void deleteNode(NODE* head, int data);

#endif // NODE_H
