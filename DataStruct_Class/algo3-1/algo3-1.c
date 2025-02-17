#include <stdio.h>
#include <stdbool.h>

#define N_MIN 3
#define N_MAX 8

int board[N_MAX][N_MAX];

// 检查放置皇后是否安全
bool isSafe(int row, int col, int n) {
    int i, j;

    // 检查列冲突
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // 检查左上冲突
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // 检查右上冲突
    for (i = row, j = col; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// 递归函数
bool solveNQueens(int row, int n) {
    if (row == n) {
        printf("解:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        printf("\t");
        return true;
    }

    bool res = false;
    // 在当前行尝试
    for (int col = 0; col < n; col++) {
        //是否安全
        if (isSafe(row, col, n)) {
            board[row][col] = 1;
            res = solveNQueens(row + 1, n) || res;
            board[row][col] = 0;
        }
    }
    return res;
}

int main() {
    int n;
    printf("输入一个数，值域[%d，%d]且为正整数: ", N_MIN, N_MAX);
    scanf("%d", &n);
        for (int i = 0; i < N_MAX; i++) {
            for (int j = 0; j < N_MAX; j++) {
                board[i][j] = 0;
                }
            }

        if (!solveNQueens(0, n)) {
            printf("无解！\n");
        }

    return 0;
}

