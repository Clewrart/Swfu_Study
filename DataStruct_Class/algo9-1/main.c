#include <stdio.h>


//二分查找
int Find(int arr[], int want, int low, int high) {
    if (low > high) {
        return -1; //未找到
    }

    int mid = low + (high - low) / 2;
    printf("本次范围[%d, %d], 中间元素：%d\n", low, high, arr[mid]);

    if (arr[mid] == want){
        return mid; //mid索引
    } else if (arr[mid] < want) {
        return Find(arr, want, mid + 1, high); //右半部分找
    } else {
        return Find(arr, want, low, mid - 1); //左半部分找
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int want;//查找
    printf("请输入用二分法查找的元素：");
    scanf("%i",&want);
    int n = sizeof(arr) / sizeof(arr[0]);


    int result = Find(arr, want, 0, n - 1);
    if (result != -1) {
        printf("找到%d，索引为%d\n", want, result);
    } else {
        printf("未找到%d。\n", want);
    }

    return 0;
}
