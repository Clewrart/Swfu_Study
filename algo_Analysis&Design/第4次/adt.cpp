#include "adt.h"
using namespace std;

int iCount = 0;
int WeiZhi[N];

// 初始化全局
void Init() {
    iCount = 0;
    for (int i = 0; i < N; ++i) {
        WeiZhi[i] = -1;
    }
}

// 输出
void Output() {
    cout << "第 " << ++iCount << " 种解法：" << endl;
    for (int row = 1; row <= N; ++row) {     // 行
        for (int col = 0; col < N; ++col) {   // 列
            if (WeiZhi[col] == row) {
                cout << "x ";
            } else {
                cout << "o ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
