#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;  // 数据
    struct Node *next; // 指向下一个结点的指针
};

typedef struct Node NODE;

// 创建链表
NODE *createList(int *a, int n);

// 输出列表元素
void outputList(NODE *head);

// 删除链表
void deleteList(NODE *head);

// 添加结点
void insertNode(NODE *head, int x);

// 删除结点
void deleteNode(NODE *head, int x);

int main()
{
    int a[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90}, i;
    NODE *head;
    printf("数组初值：");
    for(i = 0; i < 9; i++)
    {
        printf("%d\t",a[i]);
    }
    head = createList(a, 9);
    printf("\n用数组元素创建的动态链表：\n");
    outputList(head);
    printf("\n");

    //插入节点
    insertNode(head, 55);
    outputList(head);
    printf("\n");

    //删除节点
    deleteNode(head, 55);
    outputList(head);
    printf("\n");

    //删除表
    deleteList(head);
    outputList(head);
    printf("\n");

    return 0;
}

NODE *createList(int *a, int n)
{
    int i;
    NODE *head, *p, *new_node;
    head = (NODE *)malloc(sizeof(NODE));
    p = head;
    for(i = 0; i < n; i++)
    {
        new_node = (NODE *)malloc(sizeof(NODE));
        new_node->data = a[i];
        new_node->next = NULL;
        p->next = new_node;
        p = p->next;
    }
    return head;

}

// 输出列表元素
void outputList(NODE *head)
{
    NODE *p;
    p = head->next;
    while(p != NULL)
    {
        printf("%d-> ", p->data);
        p = p->next;
    }
    printf("NULL");

}

//删除链表
void deleteList(NODE *head)
{
    NODE *p1 = head;
    NODE *p2 = head->next;
    while(p1 != NULL)
    {
        free(p1);

        p1 = p2;
        p2 = p2->next;
        if(p2 != NULL)
        {
            p2 = p2->next;
        }
    }

}

//插入结点
void insertNode(NODE *head, int data)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node ->data = data;
    new_node ->next = NULL;
    NODE *p1 = head;
    NODE *p2 = head ->next;

    while (p2 != NULL)
    {
        if(p2->data < data)
        {
            p1 = p2;
            p2 = p2->next;

        }
        else
        {
            break;
        }
    }
    new_node ->next = p2;
    p1 ->next = new_node;

}

//删除结点
void deleteNode(NODE *head, int data)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node ->data = data;
    new_node ->next = NULL;
    NODE *p1 = head;
    NODE *p2 = head ->next;

    //搜索第一个比data大的结点
    while (p2 != NULL)
    {
        if(p2->data != data)
        {
            p1 = p2;
            p2 = p2->next;

        }
        else
        {
            break;
        }
    }
    p1 ->next = p2 ->next;
    free(p2);
}

