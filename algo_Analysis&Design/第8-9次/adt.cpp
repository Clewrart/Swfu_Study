#include "ADT.h"
#include <cstdlib>

using namespace std;

// 归并排序
void mergeSort(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp(n);
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = min(i + width, n);
            int right = min(i + 2 * width, n);
            int l = left, r = mid, t = left;
            while (l < mid && r < right){
                if (arr[l] <= arr[r]) {
                    temp[t] = arr[l];
                    t++;
                    l++;
                } 
                else {
                    temp[t] = arr[r];
                    t++;
                    r++;
                }
            }
            while (l < mid) {
                temp[t++] = arr[l++];
            }
            while (r < right){
              temp[t++] = arr[r++];  
            } 
            for (int j = left; j < right; j++){
                arr[j] = temp[j];
            }
                
        }
    }
}

// 快速排序
void quickSort(vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        // arr[i]<= pivot，i右移
        while (i <= j && arr[i] <= pivot) {
            i++;
        }

        // arr[j]>pivot，j左移
        while (i <= j && arr[j] > pivot) {
            j--;
        }

        // 如果i<j，错位，交换
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[low], arr[j]);
    swap(arr[low], arr[j]);
    quickSort(arr, low, j - 1);
    quickSort(arr, j + 1, high);
}

#include <vector>
#include <algorithm>
using namespace std;


// 基数排序
void radixSort256(vector<int>& arr) {
    const int BITS = 32;
    const int RADIX = 256;
    const int MASK = RADIX - 1;
    int n = static_cast<int>(arr.size());
    vector<int> temp(n);// 暂存排好序的数组

    for (int shift = 0; shift < BITS; shift += 8) {
        vector<int> count(RADIX);
        for (int k = 0; k < RADIX; ++k) {
            count[k] = 0;
        }

        for (int i = 0; i < n; ++i) {
            // 按位与
            int byteValue = (arr[i] >> shift) & MASK;
            count[byteValue] = count[byteValue] + 1;
        }

        for (int j = 1; j < RADIX; ++j) {
            count[j] = count[j] + count[j - 1];
        }

        // 从后往前遍历
        for (int i = n - 1; i >= 0; --i) {
            int byteValue = (arr[i] >> shift) & MASK;
           
            int pos = count[byteValue] - 1;
            temp[pos] = arr[i];
            count[byteValue] = pos;
        }
        for (int i = 0; i < n; ++i) {
            arr[i] = temp[i];
        }
    }

}


// 微妙时间获取
long long getMicroseconds() {
    LARGE_INTEGER freq, cnt;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&cnt);
    return (cnt.QuadPart * 1000000LL) / freq.QuadPart;
}

// 随机数生成
vector<int> RandomArray(int n) {
    vector<int> a(n);
    srand(static_cast<unsigned>(getMicroseconds()));
    for (int i = 0; i < n; ++i) {
        a[i] = rand();
    }
    return a;
}