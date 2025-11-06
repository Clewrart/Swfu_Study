#include <vector>
using namespace std;

template <class T>

class PermGen {
private:
    vector<T> elems;   // 输入元素集合
    vector<bool> used; // 元素使用状态
    vector<T> curr;    // 当前排列序列

    void next(int dep);     // 递归排列

public:
    PermGen(const vector<T>& in); // 构造函数
    void start();                     
};