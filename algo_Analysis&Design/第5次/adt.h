#ifndef ADT_H
#define ADT_H

#include <vector>

class Ma {
private:
    static const int n = 5; // 棋盘大小
    int board[n][n];       // 棋盘
    int move_x[8];         // 马的8个可能跳跃方向的X轴增量
    int move_y[8];         // 马的8个可能跳跃方向的Y轴增量
    std::vector<std::vector<int>> solutions;  // 存储所有解

    bool is_safe(int x, int y);    // 判断位置是否有效
    void ma(int x, int y, int move_count);  // 递归回溯

public:
    Ma();  // 构造函数
    void find(int start_x, int start_y); // 开始寻找路径
    void output();  // 打印所有路径
};

#endif
