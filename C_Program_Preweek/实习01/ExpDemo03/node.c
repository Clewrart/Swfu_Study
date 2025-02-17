#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"

NODE *createList(int* a, int n)
{
    if (a == NULL || n <= 0)
    {
        return NULL;
    }

    NODE *prev, *next;

    NODE *head = (NODE*)malloc(sizeof(NODE));
    NODE *p = head;
    head->data = n;

    for (int i = 0; i < n; i++)
    {
        NODE *pnode = malloc(sizeof(NODE));
        pnode->data = a[i];
        pnode->next = NULL;
        p->next = pnode;
        p = pnode;
    }

    return head;
}

void outputList(NODE* head)
{
    if (head == NULL)
    {
        return;
    }

    NODE *p = head->next;

    while (p != NULL)
    {
        printf("%d -> ", p->data);
        p = p->next;
    }

    printf("NULL\n");
}

void deleteList(NODE* head)
{
    NODE *curr = head;
    NODE *next = head->next;

    while (curr != NULL)
    {
        free(curr);
        curr = next;
        if (next != NULL)
        {
            next = next->next;
        }
    }
}

void insertNode(NODE* head, int data)
{
    NODE *pnode = malloc(sizeof(NODE));
    pnode->data = data;
    pnode->next = NULL;

    NODE *prev = head;
    NODE *next = head->next;

    while (next != NULL)
    {
        if (next->data < data)
        {
            prev = next;
            next = next->next;
        }
        else
        {
            break;
        }
    }

    pnode->next = next;
    prev->next = pnode;
}

void deleteNode(NODE* head, int data)
{
    NODE *prev = head;
    NODE *next = head->next;
    bool found = false;

    while (next != NULL)
    {
        if (next->data != data)
        {
            prev = next;
            next = next->next;
        }
        else
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        prev->next = next->next;
        free(next);
    }
}

