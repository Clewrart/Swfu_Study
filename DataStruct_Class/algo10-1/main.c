#include <stdio.h>

void oddEvenSort(int arr[], int n);
void printArray(int arr[], int n);

int main() {
    int arr[] = {34, 2, 10, -9, 7, 11,2,599 , 99,8};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("原始数组:\n");
    printArray(arr, n);

    oddEvenSort(arr, n);

    printf("\n排序后的数组:\n");
    printArray(arr, n);

    return 0;
}

// 奇偶交换排序函数
void oddEvenSort(int arr[], int n) {
    int sorted = 0; // 用于判断数组是否已经排序
    while (!sorted) {
        sorted = 1; // 假设数组已经排序

        // 处理奇数索引
        for (int i = 1; i <= n-2; i += 2) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                sorted = 0; // 发现需要交换，未完全排序
            }
        }

        // 处理偶数索引
        for (int i = 0; i <= n-2; i += 2) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                sorted = 0;
            }
        }
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}