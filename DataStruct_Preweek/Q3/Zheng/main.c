#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 100 // 定义数组最大长度
#define BLOCK_SIZE 10 // 定义分块查找的块大小

// 生成随机数组
void randomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; // 生成0-99的随机数
    }
}

// 正序顺序查找
int Findshunxu(int arr[], int size, int key, int* bijiaoci) {
    for (int i = 0; i < size; i++) {
        (*bijiaoci)++; // 比较次数增加
        if (arr[i] == key) {
            return i; // 找到关键字返回索引
        }
    }
    return -1; // 没有找到返回-1
}

// 逆序顺序查找
int Findshunxu_reverse(int arr[], int size, int key, int* bijiaoci) {
    for (int i = size - 1; i >= 0; i--) {
        (*bijiaoci)++; // 比较次数增加
        if (arr[i] == key) {
            return i; // 找到关键字返回索引
        }
    }
    return -1; // 没有找到返回-1
}


// 折半查找
int Findzheban(int arr[], int size, int key, int* bijiaoci) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        (*bijiaoci)++;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// 分块查找
int Findfenkuai(int arr[], int size, int key, int* bijiaoci) {
    int block_index = -1;
    for (int i = 0; i < size; i += BLOCK_SIZE) {
        (*bijiaoci)++;
        if (arr[i] >= key) {
            block_index = i;
            break;
        }
    }
    if (block_index == -1) {
        block_index = size - 1;
    }
    for (int i = block_index - BLOCK_SIZE; i <= block_index && i < size; i++) {
        (*bijiaoci)++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// 插值查找
int Findchazhi(int arr[], int size, int key, int* bijiaoci) {
    int low = 0, high = size - 1;
    while (low <= high && key >= arr[low] && key <= arr[high]) {
        int pos = low + ((double)(key - arr[low]) / (arr[high] - arr[low]) * (high - low));
        (*bijiaoci)++;
        if (arr[pos] == key) {
            return pos;
        } else if (arr[pos] < key) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return -1;
}

// 斐波那契查找
int Findfeibonaqie(int arr[], int size, int key, int* bijiaoci) {
    int fbnq1 = 0; // (m-2) 的斐波那契数
    int fbnq2 = 1; // (m-1) 的斐波那契数
    int fbnq = fbnq1 + fbnq2; // m 的斐波那契数

    while (fbnq < size) {
        fbnq1 = fbnq2;
        fbnq2 = fbnq;
        fbnq = fbnq1 + fbnq2;
    }

    int offset = -1;

    while (fbnq > 1) {
        int i = (offset + fbnq1 < size - 1) ? offset + fbnq1 : size - 1;
        (*bijiaoci)++;
        if (arr[i] < key) {
            fbnq = fbnq2;
            fbnq2 = fbnq1;
            fbnq1 = fbnq - fbnq2;
            offset = i;
        } else if (arr[i] > key) {
            fbnq = fbnq1;
            fbnq2 = fbnq2 - fbnq1;
            fbnq1 = fbnq - fbnq2;
        } else {
            return i;
        }
    }

    if (fbnq2 && arr[offset + 1] == key) {
        (*bijiaoci)++;
        return offset + 1;
    }

    return -1;
}

// 二叉树查找
struct TreeNode {
    int key;
    int index;
    struct TreeNode* left;
    struct TreeNode* right;
};
struct TreeNode* create_jiedian(int key, int index) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->index = index;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void charu_jiedian(struct TreeNode** root, int key, int index) {
    if (*root == NULL) {
        *root = create_jiedian(key, index);
        return;
    }
    if (key < (*root)->key) {
        charu_jiedian(&(*root)->left, key, index);
    } else {
        charu_jiedian(&(*root)->right, key, index);
    }
}

// 二叉树查找
int Finderchashu(struct TreeNode* root, int key, int* bijiaoci) {
    if (root == NULL) {
        return -1;
    }
    (*bijiaoci)++;
    if (root->key == key) {
        return root->index;
    }
    if (key < root->key) {
        return Finderchashu(root->left, key, bijiaoci);
    } else {
        return Finderchashu(root->right, key, bijiaoci);
    }
}

// 释放二叉树节点
void free_tree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// 冒泡排序，用于对数组进行排序
void sort_array(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    srand((int)time(NULL)); // 设置随机数种子

    int testTime; //测试次数
    printf("想测试多少次？: ");
    scanf("%d", &testTime);

    int testArray[testTime][MAXSIZE];// 测试数组
    int keys[testTime];//关键字
    for (int i = 0; i < testTime; i++) {
        randomArray(testArray[i], MAXSIZE); // 生成随机数组
        sort_array(testArray[i], MAXSIZE); // 对数组进行排序
        keys[i] = rand() % 100; // 生成随机关键字

    }

    for (int i = 0; i < testTime; i++) {
        int bijiaocishu = 0;
        int key = keys[i];
        int* data = testArray[i];

        printf("第%d次测试, 关键字: %d\n", i + 1, key);
        printf("本次测试数组\n");
        for (int j = 0; j < MAXSIZE; j++) {
            printf("%d\t", testArray[i][j]);
        }

        // 顺序查找
        bijiaocishu = 0;
        int result = Findshunxu(data, MAXSIZE, key, &bijiaocishu);
        if (result != -1) {
            printf("\n顺序查找找到，位置: %d, 比较次数: %d\n", result, bijiaocishu);
        } else {
            printf("\n顺序查找未找到，比较次数: %d\n", bijiaocishu);
        }

        // 折半查找
        bijiaocishu = 0;
        result = Findzheban(data, MAXSIZE, key, &bijiaocishu);
        if (result != -1) {
            printf("折半查找找到，位置: %d, 比较次数: %d\n", result, bijiaocishu);
        } else {
            printf("折半查找未找到，比较次数: %d\n", bijiaocishu);
        }

        // 分块查找
        bijiaocishu = 0;
        result = Findfenkuai(data, MAXSIZE, key, &bijiaocishu);
        if (result != -1) {
            printf("分块查找找到，位置: %d, 比较次数: %d\n", result, bijiaocishu);
        } else {
            printf("分块查找未找到，比较次数: %d\n", bijiaocishu);
        }

        // 插值查找
        bijiaocishu = 0;
        result = Findchazhi(data, MAXSIZE, key, &bijiaocishu);
        if (result != -1) {
            printf("插值查找找到，位置: %d, 比较次数: %d\n", result, bijiaocishu);
        } else {
            printf("插值查找未找到，比较次数: %d\n", bijiaocishu);
        }

        // 斐波那契查找
        bijiaocishu = 0;
        result = Findfeibonaqie(data, MAXSIZE, key, &bijiaocishu);
        if (result != -1) {
            printf("斐波那契找到，位置: %d, 比较次数: %d\n", result, bijiaocishu);
        } else {
            printf("斐波那契未找到，比较次数: %d\n", bijiaocishu);
        }

        // 二叉树查找
        struct TreeNode* root = NULL;
        for (int j = 0; j < MAXSIZE; j++) {
            charu_jiedian(&root, data[j], j); // 构建二叉树并保存索引
        }
        bijiaocishu = 0;
        result = Finderchashu(root, key, &bijiaocishu);
        if (result != -1) {
            printf("二叉树查找到，位置: %d, 比较次数: %d\n", result, bijiaocishu);
        } else {
            printf("二叉树查未找到，比较次数: %d\n", bijiaocishu);
        }
        free_tree(root); // 释放二叉树

        printf("\n");
    }

    return 0;
}
