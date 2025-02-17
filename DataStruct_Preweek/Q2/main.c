#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100   // 初始栈大小
#define STACKINCREMENT 10     // 栈增量

// 定义迷宫中的位置结构
struct Position {
    int x;
    int y;
};

// 定义栈元素结构
struct SElement {
    int ord;       // 序号，表示步数
    struct Position p; // 当前坐标
    int di;        // 当前方向
    int d;         // 记录方向的数字值
};

// 定义栈结构
struct MyStack {
    struct SElement* base; // 栈底指针
    struct SElement* top;  // 栈顶指针
    int stacksize;         // 栈的当前大小
};

// 初始化栈
int InitStack(struct MyStack* s) {
    s->base = (struct SElement*)malloc(STACK_INIT_SIZE * sizeof(struct SElement));
    if (!s->base) return 0; // 分配失败
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
    return 1; // 初始化成功
}

// 判断栈是否为空
int IsStackEmpty(struct MyStack* s) {
    return s->top == s->base;
}

// 获取栈顶元素
int GetTop(struct MyStack* s, struct SElement* e) {
    if (IsStackEmpty(s)) return 0; // 栈为空
    *e = *(s->top - 1);
    return 1;
}

// 获取栈长度
int StackLength(struct MyStack* s) {
    return s->top - s->base;
}

// 向栈中压入元素
int Push(struct MyStack* s, struct SElement e) {
    if (s->top - s->base >= s->stacksize) { // 栈满，进行扩展
        s->base = (struct SElement*)realloc(s->base, (s->stacksize + STACKINCREMENT) * sizeof(struct SElement));
        if (!s->base) return 0; // 分配失败
        s->top = s->base + s->stacksize;
        s->stacksize += STACKINCREMENT;
    }
    *(s->top++) = e;
    return 1; // 压栈成功
}

// 从栈中弹出元素
int Pop(struct MyStack* s, struct SElement* e) {
    if (IsStackEmpty(s)) return 0; // 栈为空
    *e = *(--s->top);
    return 1; // 弹栈成功
}

#define m 11 // 列数
#define n 10 // 行数

// 迷宫数组，1表示障碍，0表示通路
int miGong[m][n] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,1,1},
    {1,0,1,1,1,0,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,1,1},
    {1,0,1,1,1,1,0,0,1,1},
    {1,1,1,0,0,0,1,0,1,1},
    {1,1,1,0,0,0,0,0,0,1}
};

// 判断当前位置是否可以通过
int Pass(struct Position posi) {
    return miGong[posi.x][posi.y] == 0;
}

// 获取下一个位置
struct Position xiageweizhi(struct Position now, int direction) {
    struct Position next;
    int x = now.x;
    int y = now.y;
    switch (direction) {
    case 1: // 向右
        next.x = x;
        next.y = y + 1;
        break;
    case 2: // 向下
        next.x = x + 1;
        next.y = y;
        break;
    case 3: // 向左
        next.x = x;
        next.y = y - 1;
        break;
    case 4: // 向上
        next.x = x - 1;
        next.y = y;
        break;
    default:
        break;
    }
    return next;
}

// 标记足迹
void foot(struct Position p, int step) {
    miGong[p.x][p.y] = step;
}

// 标记已走过的路
void MarkPrint(struct Position p) {
    miGong[p.x][p.y] = 99;
}

// 显示迷宫
void Display_migong() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (miGong[i][j] < 0)
                printf("%d ", miGong[i][j]);
            else if (miGong[i][j] < 10)
                printf("%d  ", miGong[i][j]);
            else
                printf("%d ", miGong[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct MyStack path;
    InitStack(&path); // 初始化栈
    struct Position curp;

    curp.x = 1;
    curp.y = 1;
    int curStep = 1;

    printf("起点坐标：(%d, %d)\n", curp.x, curp.y);

    do {
        if (Pass(curp)) { // 判断当前位置是否可通过
            foot(curp, curStep); // 标记足迹
            struct SElement e;
            e.di = 1; // 初始方向为向右
            e.ord = curStep; // 当前步数
            e.p.x = curp.x;
            e.p.y = curp.y;
            e.d = 1; // 记录方向
            Push(&path, e); // 将当前位置压入栈
            if (curp.x == m - 2 && curp.y == n - 2) break; // 到达终点
            curp = xiageweizhi(curp, 1); // 移动到下一个位置
            curStep++;
        } else {
            if (!IsStackEmpty(&path)) {
                struct SElement e;
                Pop(&path, &e); // 弹出当前位置
                curStep--;
                while (e.di == 4 && !IsStackEmpty(&path)) {
                    MarkPrint(e.p); // 标记已走过的路
                    Pop(&path, &e);
                    curStep--;
                }
                if (e.di < 4) {
                    curp = xiageweizhi(e.p, e.di + 1); // 改变方向
                    e.di++;
                    e.d = e.di; // 更新方向信息
                    curStep++;
                    Push(&path, e); // 将新位置压入栈
                }
            }
        }
    } while (!IsStackEmpty(&path));

    printf("通路:\n");

    // 使用数组存储路径，以便逆序输出
    struct SElement* pathArray = (struct SElement*)malloc(StackLength(&path) * sizeof(struct SElement));
    int index = 0;
    while (!IsStackEmpty(&path)) {
        Pop(&path, &pathArray[index]);
        index++;
    }

    // 逆序输出路径
    for (int i = index - 1; i >= 0; i--) {
        printf("(%d, %d, %d) ", pathArray[i].p.x, pathArray[i].p.y, pathArray[i].d);
    }

    printf("\n最终迷宫图：\n");
    Display_migong();

    free(pathArray); // 释放动态分配的路径数组内存

    return 0;
}
