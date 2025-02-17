#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 8
#define MAX_STEPS (N * N)

// 8个方向
int HTry1[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int HTry2[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// 栈结构，保存当前位置和方向
typedef struct {
    int x;
    int y;
    int dir; // 方向
} StackNode;

int board[N][N];
StackNode stack[MAX_STEPS];
int top = -1;

void init_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1; // 初始化棋盘，未访问标记为-1
        }
    }
}

// 检查位置1在棋盘内？2未经过？
bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// 当前位置入栈中并标记
void push_stack(int x, int y, int d) {
    top++;
    stack[top].x = x;
    stack[top].y = y;
    stack[top].dir = d;
    board[x][y] = top + 1; // 步数标记
}

// 弹出栈顶位置，并将其在棋盘上标记为未访问
void pop_stack() {
    int x = stack[top].x;
    int y = stack[top].y;
    board[x][y] = -1;
    top--;
}

// 输出当前棋盘状态
void print_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == -1) {
                printf(" X ");
            } else {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
int jsq =1;

// 回溯法跑马
void Line(int start_x, int start_y) {
    init_board(); // 初始化棋盘
    push_stack(start_x, start_y, 0); // 将起始位置推入栈中


    while (top > -1) { // 当栈非空时
        if (top == MAX_STEPS - 1) { // 如果遍历完所有位置

            printf("找到%d条马行走路线:\n",jsq++);
            print_board(); // 输出当前棋盘状态

            pop_stack(); // 弹出栈顶，寻找下一条路径
            continue;
        }

        int move_x = stack[top].x; // 当前x坐标
        int move_y = stack[top].y; // 当前y坐标
        int d = stack[top].dir; // 当前方向
        bool moved = false; // 标记是否有移动

        // 尝试8个方向
        while (d < 8) {
            int new_x = move_x + HTry1[d];
            int new_y = move_y + HTry2[d];
            if (isValid(new_x, new_y)) {
                stack[top].dir = d + 1; // 更新当前方向
                push_stack(new_x, new_y, 0); // 将新位置推入栈中
                moved = true;
                break;
            }
            d++;
        }

        // 如果没有有效的移动方向，则回溯
        if (!moved) {
            pop_stack();
            if (top >= 0) {
                stack[top].dir++; // 更新回溯位置的方向
            }
        }
    }
}

int main() {
    srand(time(NULL)); // 设置随机种子
    int start_x, start_y;
    printf("请输入起始位置 x (0 ~ 7): ");
    scanf("%d", &start_x);
    printf("请输入起始位置 y (0 ~ 7): ");
    scanf("%d", &start_y);


    // 检查起始位置是否有效
    if (start_x < 0 || start_x >= N || start_y < 0 || start_y >= N) {
        printf("无效的起始位置\n");
        return 1;
    }

    Line(start_x, start_y); // 执行
    return 0;
}
