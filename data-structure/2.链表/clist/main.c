#include <stdio.h>

#include "clist.h"

// TODO:
void print_clist(struct CList *list) {
    struct CListNode *p = list->head;

    if (clist_size(list) == 0) {
        return;
    }

    while (p->next != list->head) {
        printf("%lf ", p->data);
        p = p->next;
    }
    printf("%f\n", p->data);
}

int main() {
    struct CList list;
    int i;

    clist_init(&list);

    printf("Insert 0-4\n");
    for (i = 0; i < 5; i++) {
        clist_insert_after(&list, list.head, i);
    }
    print_clist(&list);

    // Remove 2 elements
    printf("Remove 2 elements\n");
    for (i = 0; i < 2; i++) {
        clist_remove_after(&list, list.head);
    }
    print_clist(&list);

    printf("size: %d\n", list.size);

    clist_destroy(&list);

    return 0;
}