#include "sort.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void insertion_sort_basical(int *a, int n, int d, int (*comp)(const void *, const void *)) {
    for (int i = d; i < n - d + 1; i += d) {
        int mid = i;

        for (int j = i - d; j >= 0; j -= d) {
            if (comp(a + mid, a + j) < 0) {
                SWAP(a[mid], a[j], int);
                mid = j;
            } else {
                break;
            }
        }
    }
}

// TODO:
// 插入排序
void insertion_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    insertion_sort_basical(a, n, 1, comp);
}

// TODO:
// 希尔排序
void shell_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    int prime[15] = {1, 3, 7, 17, 31, 67, 113, 227, 397, 499, 971, 1667, 3049, 6133, 10799};

    for (int i = 14; i >= 0; i--) {
        int dis = prime[i];

        if (dis < n) {
            insertion_sort_basical(a, n, dis, comp);
        }
    }
}

// TODO: DONE
// 选择排序
void selection_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    for (int i = 0; i < n; i++) {
        int k = i;

        for (int j = i + 1; j < n; j++) {
            if (comp(&a[j], &a[k]) < 0) {
                k = j;
            }
        }

        if (k != i) {
            SWAP(a[i], a[k], int);
        }
    }
}

void adjust(int *a, int x, int n, int (*comp)(const void *, const void *)) {
    int *p = a + x;

    while (p - a < n) {
        int *lc = a + 2 * (x + 1) - 1;
        int *rc = a + 2 * (x + 1);

        if (comp(lc, rc) < 0) {
            if (comp(p, lc) > 0 && lc - a < n) {
                SWAP(*p, *lc, int);
                x = lc - a;
                p = lc;
            } else {
                break;
            }
        } else {
            if (comp(p, rc) > 0 && rc - a < n) {
                SWAP(*p, *rc, int);
                x = rc - a;
                p = rc;
            } else {
                break;
            }
        }
    }
}

// TODO:
// 堆排序
void heap_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    int *c = malloc(sizeof(int) * (n)), index = 0;

    for (int i = (n - 2) / 2; i >= 0; i--) {
        adjust(a, i, n, comp);
    }

    for (int i = 0; i < n; i++) {
        c[index++] = a[0];
        a[0] = a[n - i - 1];
        adjust(a, 0, n - i - 1, comp);
    }

    memcpy(a, c, (n) * sizeof(int));
    free(c);
}

// TODO:
// 冒泡排序
void bubble_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comp(a + j, a + j + 1) > 0) {
                SWAP(a[j], a[j + 1], int);
            }
        }
    }
}

// TODO:
// 快速排序
void quick_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    int *left = a + 1, *right = a + n - 1;

    while (left <= right) {
        while (comp(left, a) < 0 && left - a < n - 1) {
            left++;
        }
        while (comp(right, a) > 0 && right - a > 0) {
            right--;
        }

        if (left < right) {
            SWAP(*left, *right, int);
        } else {
            SWAP(*a, *right, int);
            break;
        }
    }

    if (right - a > 1) {
        quick_sort(a, right - a, comp);
    }
    if (n - (left - a) > 1) {
        quick_sort(left, n - (left - a), comp);
    }
}

void merge_sort_basical(int *a, int n1, int *b, int n2, int (*comp)(const void *, const void *)) {
    int *c = malloc(sizeof(int) * (n1 + n2));
    int *p1 = a, *p2 = b, x = 0;

    while (p1 - a < n1 || p2 - b < n2) {
        if (p1 - a >= n1) {
            memcpy(c + x, p2, (n2 - (p2 - b)) * sizeof(int));
            break;
        } else if (p2 - b >= n2) {
            memcpy(c + x, p1, (n1 - (p1 - a)) * sizeof(int));
            break;
        } else if (comp(p1, p2) < 0) {
            c[x++] = *p1;
            p1++;
        } else {
            c[x++] = *p2;
            p2++;
        }
    }

    memcpy(a, c, (n1 + n2) * sizeof(int));
    free(c);
}

// TODO:
// 归并排序
void merge_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    if (n == 1) {
        return;
    }

    merge_sort(a, n / 2, comp);
    merge_sort(a + n / 2, n - n / 2, comp);

    merge_sort_basical(a, n / 2, a + n / 2, n - n / 2, comp);
}

int distribution(int *a, int n, int x, struct List *l, int (*comp)(const void *, const void *)) {
    int flag = 0;

    for (int i = 0; i < n; i++) {
        long long x1 = pow(10, x);
        long long x2 = pow(10, x - 1);

        if (x2 < a[i]) {
            flag = 1;
        }

        list_push_back(&l[a[i] % x1 / x2], a[i]);
    }

    return flag;
}

void collect(int *a, struct List *l, int (*comp)(const void *, const void *)) {
    int index = 0;

    for (int i = 0; i < 10; i++) {
        while (list_size(&l[i]) != 0) {
            a[index++] = l[i].head->data;
            list_pop_front(&l[i]);
        }
    }
}

// TODO:
// 基数排序
void radix_sort(int *a, int n, int (*comp)(const void *, const void *)) {
    struct List l[10];
    int turn = 1;

    for (int i = 0; i < 10; i++) {
        list_init(&l[i]);
    }

    while (distribution(a, n, turn++, l, comp) != 0) {
        collect(a, l, comp);
    }
}
