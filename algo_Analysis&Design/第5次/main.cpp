#include <iostream>
#include "adt.h"

using namespace std;

int main() {
    Ma ma;  // 创建 Ma 类的对象

    // 设置起始点，假设从 (0, 0) 开始
    cout << "寻找从 (0, 0) 开始的所有可能解..." << endl;

    // 调用 find() 方法，开始搜索所有路径
    ma.find(0, 0);

    // 打印所有解
    ma.output();

    return 0;
}
