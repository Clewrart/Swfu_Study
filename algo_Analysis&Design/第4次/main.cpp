#include <iostream>
#include "adt.h"

using namespace std;

// 八皇后递归放置
void EightQueen(int n) {
    if (n == N) { // 成功放置了8个皇后
        Output();
        return;
    }

    for (int i = 1; i <= N; ++i) { // 尝试将第n个皇后放在第i行
        WeiZhi[n] = i;
        bool conflict = false;
        for (int j = 0; j < n; ++j) {
            if (WeiZhi[j] == WeiZhi[n] || abs(WeiZhi[j] - WeiZhi[n]) == (n - j)) {
                conflict = true; // 同行或对角线冲突
                break;
            }
        }
        if (!conflict) {
            EightQueen(n + 1); // 放置下一个皇后
        }
    }
}

int main() {
    Init();          // 初始化数据
    EightQueen(0);   // 从第0列开始放置皇后
    return 0;
}
