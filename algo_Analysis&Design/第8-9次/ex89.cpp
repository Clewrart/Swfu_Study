#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "ADT.h"



int main() {
    const int SIZE = 10000;
    vector<int> original = RandomArray(SIZE);

    // 归并排序
    vector<int> a1 = original;
    long long t1 = getMicroseconds();
    mergeSort(a1);
    t1 = getMicroseconds() - t1;
    cout << "MergeSort " << t1 << "\n";

    // 快速排序
    vector<int> a2 = original;
    long long t2 = getMicroseconds();
    quickSort(a2, 0, SIZE - 1);
    t2 = getMicroseconds() - t2;
    cout << "QuickSort: " << t2 << "\n";

    // 基数排序
    vector<int> a3 = original;
    long long t3 = getMicroseconds();
    radixSort256(a3);
    t3 = getMicroseconds() - t3;
    cout << "256Sort:" << t3 << " \n";

    return 0;
}