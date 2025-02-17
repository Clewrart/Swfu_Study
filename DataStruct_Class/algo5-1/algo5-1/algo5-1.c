#include <stdio.h>

void reverseArray(int A[], int start, int end) {
    while (start < end) {
        int temp = A[start];
        A[start] = A[end];
        A[end] = temp;
        start++;
        end--;
    }
}

void swap(int A[], int n, int p0, int p1, int p2, int p3) {
    // p0 to p1
    reverseArray(A, p0, p1);
    // p2 to p3
    reverseArray(A, p2, p3);
    //all
    reverseArray(A, 0, n - 1);
}

int main() {
    int n, p0, p1, p2, p3;

    printf("请输入数组长度：");
    scanf("%d", &n);

    int A[n];
    printf("请输入数组元素，以空格分隔：");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf("请指定第几个元素是p0, p1, p2, p3（从0开始）：");
    scanf("%d %d %d %d", &p0, &p1, &p2, &p3);

    swap(A, n, p0, p1, p2, p3);

    printf("反转结果:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}

