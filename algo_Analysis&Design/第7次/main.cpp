#include "adt.h"
#include <iostream>
#include <vector>

using namespace std;

// 从整数n开始启动划分
void ADT::start(int n) {
    vector<int> path; // 当前划分路径
    divide(n, n, path); // 初始时最大值等于 n 本身
}

void ADT::divide(int left, int max, vector<int>& path) {
    if (left == 0) {
        // 输出合法划分路径
        for (int i = 0; i < path.size(); i++) {
            if (i != 0) cout << " + ";
            cout << path[i];
        }
        cout << endl;
        return;
    }

    // max开始递减，尝试可用划分数
    for (int i = min(left, max); i >= 1; i--) {
        path.push_back(i);// 当前
        divide(left - i, i, path);// 剩余递归
        path.pop_back();// 回溯
    }
}

int main() {
    ADT adt;
    int num;

    cout << "输正整数：";
    cin >> num;
    if (num <= 0) {// 判定输入合法
        cout << "必须输入一个正整数！" << endl;
        return 1;
    }

    cout << num << " 的所有整数划分如下：" << endl;
    adt.start(num);

    return 0;
}
