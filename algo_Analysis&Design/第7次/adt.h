#include <vector>

using namespace std;

class ADT {
public:
    // 启动划分
    void start(int n);

    // 递归产生划分组合
    void divide(int left, int max, vector<int>& path);
};
