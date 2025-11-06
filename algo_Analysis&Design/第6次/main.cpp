#include "adt.h"
#include <iostream>
#include <algorithm>

using namespace std; 

template <class T>
PermGen<T>::PermGen(const vector<T>& in) {
    elems = in;
    sort(elems.begin(), elems.end()); // 排序便于跳过重复项
    used.resize(elems.size(), false); // 初始都未使用
}

template <class T>
void PermGen<T>::start() {
    next(0);
}

// 递归排列
template <class T>
void PermGen<T>::next(int dep) {
    if (dep == elems.size()) {
        for (const T& x : curr) {
            cout << x << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < elems.size(); i++) {
        if (used[i]) continue;

        // 跳过前一个相同但未使用的元素
        if (i > 0 && elems[i] == elems[i - 1] && !used[i - 1]) continue;

        used[i] = true;
        curr.push_back(elems[i]);
        next(dep + 1);
        curr.pop_back();
        used[i] = false;
    }
}

int main() {
    cout << "字符：" << endl;
    vector<char> in1 = {'X', 'C', 'X'};
    PermGen<char> gen1(in1);
    gen1.start();

    cout << "数字：" << endl;
    vector<int> in2 = {1, 3, 2, 3};
    PermGen<int> gen2(in2);
    gen2.start();

    return 0;
}
