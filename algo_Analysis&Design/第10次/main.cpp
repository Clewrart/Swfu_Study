#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "ADT.h"

using namespace std;

// 二分查找
Search binSearch(const vector<int>& arr, int x) {
    int low = 0, high = arr.size() - 1;
    int mid;
    int i = -1, j = -1;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            return Search(mid, mid);
        } else if (arr[mid] < x) {
            i = mid;
            low = mid + 1;
        } else {
            j = mid;
            high = mid - 1;
        }
    }

    return Search(i, j);
}

// 随机生成排序数组
vector<int> generateSortedArray(int n, int maxVal = 100) {
    vector<int> arr(n);
    srand((unsigned int)time(0));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % maxVal;
    }
    sort(arr.begin(), arr.end());
    return arr;
}

// 打印数组
void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

// 主函数
int main() {
    int n, x;
    cout << "请输入数组大小 n: ";
    cin >> n;

    vector<int> arr = generateSortedArray(n);
    cout << "排序后的随机数组: ";
    printArray(arr);

    cout << "请输入要搜索的元素 x: ";
    cin >> x;

    Search result = binSearch(arr, x);
    cout << "结果: i = " << result.i << ", j = " << result.j << endl;

    if (result.i >= 0) cout << "arr[i] = " << arr[result.i] << endl;
    else cout << "不存在小于x的元素" << endl;

    if (result.j >= 0) cout << "arr[j] = " << arr[result.j] << endl;
    else cout << "不存在大于x的元素" << endl;

    return 0;
}
