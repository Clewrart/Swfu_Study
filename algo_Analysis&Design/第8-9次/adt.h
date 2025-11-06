#ifndef ADT_H
#define ADT_H

#include <vector>
#include <windows.h>

using namespace std;

// 非递归归并排序
void mergeSort(vector<int>& arr);

// 快速排序
void quickSort(vector<int>& arr, int low, int high);

// 基数排序256为基数
void radixSort256(vector<int>& arr);

// 获取微秒级时间戳
long long getMicroseconds();

// 生成随机整数数组
vector<int> RandomArray(int n);

#endif
