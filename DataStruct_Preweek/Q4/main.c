#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100
//10000个数随机取100个参与
// 记录比较次数和移动次数
typedef struct {
    int bijiao;
    int yidong;
} Metrics;



// 正序数组
void zhengxuArray(int *array, int size) {
    int d =  rand() % 10000 ;
    for (int i = 0; i < size; i++) {
        array[i] =  d+i;
    }
}

// 逆序数组
void NixuArray(int *array, int size) {
     int c = rand() % 10000;
    for (int i = 0; i < size; i++) {
        array[i] =  c-i;
    }
}
// 乱序随机
void RondomArray(int *array, int size) {

    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000;
    }
}

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}



// 冒泡
void SortMaopao(int *array, int size, Metrics *metrics) {
    metrics->bijiao = 0;
    metrics->yidong = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            metrics->bijiao++;
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                metrics->yidong += 3; //每进行一次交换，移动次数加三
            }
        }
    }
}

// 直接插入
void SortZhijiecharu(int *array, int size, Metrics *metrics) {
    metrics->bijiao = 0;
    metrics->yidong = 0;
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        metrics->yidong++;
        while (j >= 0 && array[j] > key) {
            metrics->bijiao++;
            array[j + 1] = array[j];
            metrics->yidong++;
            j--;
        }
        if (j >= 0) {
            metrics->bijiao++;
        }
        array[j + 1] = key;
        metrics->yidong++;
    }
}

// 简单选择
void SortJiandanxuanze(int *array, int size, Metrics *metrics) {
    metrics->bijiao = 0;
    metrics->yidong = 0;
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            metrics->bijiao++;
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = array[i];
            array[i] = array[minIndex];
            array[minIndex] = temp;
            metrics->yidong += 3; // 交换1=移动
        }
    }
}

// 快速排序自行辅助
void SortKuaisuTemp(int *array, int low, int high, Metrics *metrics) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            metrics->bijiao++;
            if (array[j] < pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                metrics->yidong += 3; // 每次交换算作三次移动
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;
        metrics->yidong += 3; // 交换算作三次移动

        int pi = i + 1;
        SortKuaisuTemp(array, low, pi - 1, metrics);
        SortKuaisuTemp(array, pi + 1, high, metrics);
    }
}

// 快速
void SortKuaisu(int *array, int size, Metrics *metrics) {
    metrics->bijiao = 0;
    metrics->yidong = 0;
    SortKuaisuTemp(array, 0, size - 1, metrics);
}

// 希尔
void SortXier(int *array, int size, Metrics *metrics) {
    metrics->bijiao = 0;
    metrics->yidong = 0;
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = array[i];
            int j;
            metrics->yidong++;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                metrics->bijiao++;
                array[j] = array[j - gap];
                metrics->yidong++;
            }
            if (j >= gap) {
                metrics->bijiao++;
            }
            array[j] = temp;
            metrics->yidong++;
        }
    }
}

// 生成最小堆数组
void zuixiaodui(int *array, int size, int i, Metrics *metrics) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size) {
        metrics->bijiao++;
        if (array[left] > array[largest]) {
            largest = left;
        }
    }

    if (right < size) {
        metrics->bijiao++;
        if (array[right] > array[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        metrics->yidong += 3;
        zuixiaodui(array, size, largest, metrics);
    }
}

// 堆排序
void SortDui(int *array, int size, Metrics *metrics) {
    metrics->bijiao = 0;
    metrics->yidong = 0;
    for (int i = size / 2 - 1; i >= 0; i--) {
        zuixiaodui(array, size, i, metrics);
    }

    for (int i = size - 1; i >= 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        metrics->yidong += 3;
        zuixiaodui(array, i, 0, metrics);
    }
}




//正序
void testzheng()
{
    int array[ARRAY_SIZE];
    int tempArray[ARRAY_SIZE];
    Metrics metrics;
    void (*sorts[])(int*, int, Metrics*) = {
        SortMaopao,
        SortZhijiecharu,
        SortJiandanxuanze,
        SortKuaisu,
        SortXier,
        SortDui
    };
    char *sortNames[] = {
        "冒泡排序",
        "直接插入排序",
        "简单选择排序",
        "快速排序",
        "希尔排序",
        "堆排序"
    };
    for (int zx = 0; zx < 5; zx++)
    {
        zhengxuArray(array, ARRAY_SIZE);
        printf("第%d正序测试，测试序列为",zx+1);
        printArray(array, ARRAY_SIZE);
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                tempArray[j] = array[j];
            }
            // 调用排序函数记录
            sorts[i](tempArray, ARRAY_SIZE, &metrics);
            printf("%s: 比较次数 = %d, 移动次数 = %d\n", sortNames[i], metrics.bijiao, metrics.yidong);
        }
        printf("\n");
    }
}


void testNi() {
    int array[ARRAY_SIZE];
    int tempArray[ARRAY_SIZE];
    Metrics metrics;
    void (*sorts[])(int*, int, Metrics*) = {
        SortMaopao,
        SortZhijiecharu,
        SortJiandanxuanze,
        SortKuaisu,
        SortXier,
        SortDui
    };
    char *sortNames[] = {
        "冒泡排序",
        "直接插入排序",
        "简单选择排序",
        "快速排序",
        "希尔排序",
        "堆排序"
    };
        for (int nx = 0; nx < 5; nx++)
        {
            NixuArray(array, ARRAY_SIZE);
            printf("第%d逆序测试，测试序列为",nx+1);
            printArray(array, ARRAY_SIZE);
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < ARRAY_SIZE; j++) {
                    tempArray[j] = array[j];
                }
                sorts[i](tempArray, ARRAY_SIZE, &metrics);
                printf("%s: 比较次数 = %d, 移动次数 = %d\n", sortNames[i], metrics.bijiao, metrics.yidong);
            }
            printf("\n");
        }
}

void testluan() {
    int array[ARRAY_SIZE];
    int tempArray[ARRAY_SIZE];
    Metrics metrics;

    // 存储各排序
    void (*sorts[])(int*, int, Metrics*) = {
        SortMaopao,
        SortZhijiecharu,
        SortJiandanxuanze,
        SortKuaisu,
        SortXier,
        SortDui
    };
    char *sortNames[] = {
        "冒泡排序",
        "直接插入排序",
        "简单选择排序",
        "快速排序",
        "希尔排序",
        "堆排序"
    };
    for (int lx = 0; lx < 5; lx++) {
        RondomArray(array, ARRAY_SIZE); // 生成随机数组
        printf("第%d乱序测试，测试序列为\n", lx+1);
        printArray(array, ARRAY_SIZE);
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                tempArray[j] = array[j];
            }

            sorts[i](tempArray, ARRAY_SIZE, &metrics);
            printf("%s: 比较次数 = %d, 移动次数 = %d\n", sortNames[i], metrics.bijiao, metrics.yidong);
        }
        printf("\n");
    }
}

int main() {
    srand((unsigned)time(NULL)); // 设置随机数种子
    testluan();
    testzheng();
    testNi();
    return 0;
}
