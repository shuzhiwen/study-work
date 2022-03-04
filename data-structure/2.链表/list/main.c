#include <stdio.h>
#include <stdlib.h>

#include "sorted_list.h"

void print_list(struct List *list) {
    struct ListNode *p = list->head;

    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}

int main() {
    struct List a, b, dst, *p = (struct List *)malloc(sizeof(struct List) * 3);
    int i;

    list_init(&a);
    list_init(&b);
    list_init(&dst);
    for (i = 0; i < 3; i++) {
        list_init(&p[i]);
    }

    for (i = 2; i < 7; i++) {
        list_push_back(&p[0], i);
        list_push_back(&a, i);
    }
    for (i = 2; i < 5; i++) {
        list_push_back(&p[1], i);
        list_push_back(&b, i);
    }
    for (i = 3; i < 6; i++) {
        list_push_back(&p[2], i);
    }

    merge_sorted_lists(&dst, &a, &b);
    print_list(&dst);
    printf("szie : %d\n", dst.size);

    list_destroy(&dst);
    list_init(&dst);

    merge_multiple_lists(&dst, &p, 3);
    print_list(&dst);
    printf("szie : %d\n", dst.size);

    list_destroy(&a);
    list_destroy(&b);
    list_destroy(&dst);

    return 0;
}