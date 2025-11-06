#ifndef SEARCH_H
#define SEARCH_H

struct Search {
    int i; // 小于x的最大元素位置
    int j; // 大于x的最小元素位置

    Search(int left = -1,  int right = -1) : i(left), j(right) {}
};

#endif
