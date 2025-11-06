#include "adt.h"
#include <iostream>
#include <vector>

using namespace std;

// 构造函数，初始化马的移动方向
Ma::Ma() {
    move_x[0] = 2; move_y[0] = 1;
    move_x[1] = 1; move_y[1] = 2;
    move_x[2] = -1; move_y[2] = 2;
    move_x[3] = -2; move_y[3] = 1;
    move_x[4] = -2; move_y[4] = -1;
    move_x[5] = -1; move_y[5] = -2;
    move_x[6] = 1; move_y[6] = -2;
    move_x[7] = 2; move_y[7] = -1;
}

// 判断位置是否有效
bool Ma::is_safe(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

// 递归回溯算法：寻找所有路径
void Ma::ma(int x, int y, int move_count) {
    // 如果遍历了所有格子
    if (move_count == n * n) {
        // 记录当前路径
        vector<int> current_solution;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                current_solution.push_back(board[i][j]);
            }
        }
        solutions.push_back(current_solution);
        return;
    }

    // 尝试8个方向
    for (int i = 0; i < 8; i++) {
        int new_x = x + move_x[i];
        int new_y = y + move_y[i];
        if (is_safe(new_x, new_y)) {
            board[new_x][new_y] = move_count;
            ma(new_x, new_y, move_count + 1); // 继续递归查找
            // 回溯
            board[new_x][new_y] = -1;
        }
    }
}

// 开始寻找路径
void Ma::find(int start_x, int start_y) {
    // 初始化棋盘
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = -1;  // -1表示该格子未访问
        }
    }

    // 从指定位置开始
    board[start_x][start_y] = 0; // 从起始位置开始
    ma(start_x, start_y, 1);
}

int number = 0;
// 打印所有路径
void Ma::output() {
    if (solutions.empty()) {
        cout << "没有找到" << endl;
    } else {
        for (const auto& solution : solutions) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << solution[i * n + j] << "\t";  // 打印每个格子的访问顺序
                }
                cout << endl;
            }
            cout <<"当前共找到"<< number+1 <<"种"<< endl;
            cout <<"———————————————————————"<< endl;
            number++;
        }
    }
}
