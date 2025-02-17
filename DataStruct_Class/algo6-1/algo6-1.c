#include <stdio.h>
#include <stdlib.h>



//二叉树
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


#define MAX_STACK_SIZE 10000
//栈构造
typedef struct Stack {

    TreeNode* data[MAX_STACK_SIZE];
    int top;
} Stack;
//初始栈
void initStack(Stack* S) {
    S->top = -1;
}
//栈空？
int isStackEmpty(Stack* S) {
    return S->top == -1;
}
//入栈
void push(Stack* S, TreeNode* node) {
    if (S->top < MAX_STACK_SIZE - 1) {
        S->data[++S->top] = node;
    }
}
//出栈
TreeNode* pop(Stack* S) {
    if (!isStackEmpty(S)) {
        return S->data[S->top--];
    }
    return NULL;
}
//获取栈顶
TreeNode* getTop(Stack* S) {
    if (!isStackEmpty(S)) {
        return S->data[S->top];
    }
    return NULL;
}



//中序遍历，非递归
void inOrder_Budigui(TreeNode* root) {
    Stack S;
    initStack(&S);
    TreeNode* p = root;

    while (p != NULL || !isStackEmpty(&S)) {
        while (p != NULL) {
            push(&S, p);
            p = p->left;
        }

        if (!isStackEmpty(&S)) {
            p = pop(&S);
            printf("%d ", p->data);
            p = p->right;
        }
    }
}

//先序遍历，递归
void preOrder_Digui(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder_Digui(root->left);
        preOrder_Digui(root->right);
    }
}

//中序遍历，递归
void inOrder_Digui(TreeNode* root) {
    if (root != NULL) {
        inOrder_Digui(root->left);
        printf("%d ", root->data);
        inOrder_Digui(root->right);
    }
}

//后序遍历，递归
void postOrder_Digui(TreeNode* root) {
    if (root != NULL) {
        postOrder_Digui(root->left);
        postOrder_Digui(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    // 创建二叉树 1-2/3 2-4/5 3-6/7 4-8/9
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->left->left->left = createNode(8);
    root->left->left->right = createNode(9);
    printf("\n20222601017 郭思宇 2022计算机科学与技术");
    printf("\n--------------------------------------------");

    printf("\n|  非递归中序遍历结果为：");
    inOrder_Budigui(root);
    printf("  |");
    printf("\n|  用递归中序遍历结果为：");
    inOrder_Digui(root);
    printf("  |");

    printf("\n|  用递归先序遍历结果为：");
    preOrder_Digui(root);
    printf("  |");

    printf("\n|  用递归后序遍历结果为：");
    postOrder_Digui(root);
    printf("  |");
    printf("\n--------------------------------------------");

    return 0;
}
