#include "search.h"

#include <stdlib.h>

// TODO:
// 使用comp对students进行排序
void sort(struct Vector *students, StudentComp comp) {
    qsort(students->buffer, students->size, sizeof(DataType), comp);
}

// TODO:
// 在students中查找stu，使用comp进行比较
// 返回查找元素的下标，如果找不到返回-1
int search(struct Vector *students, struct Student *stu, StudentComp comp) {
    for (int i = 0; i < students->size; i++) {
        if (comp(&students->buffer[i], stu) == 0) {
            return i;
        }
    }

    return -1;
}

// TODO:
// 在students中用二分查找stu，使用comp进行比较
// 返回查找元素的下标，如果找不到返回-1
int bin_search(struct Vector *students, struct Student *stu, StudentComp comp) {
    int left = 0, right = students->size - 1;

    sort(students, comp);
    while (left <= right) {
        int mid = (left + right) / 2;
        int ans = comp(&students->buffer[mid], stu);

        if (ans == 0) {
            return mid;
        }
        if (ans < 0) {
            left = mid + 1;
        }
        if (ans > 0) {
            right = mid - 1;
        }
    }

    return -1;
}
