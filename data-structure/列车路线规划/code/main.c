#include <stdio.h>

#include "init_help.h"
#include "vector.h"
#include "window.h"

int main() {
    printf("\n\n\tThe system is loading, please wait...\n\n");

    struct trietree *T = NULL;
    struct Vector vec;

    station_init(&vec);
    T = trietree_build_stat(&vec);
    printf("\n\t     Route init failed : %d\n", route_init(T, &vec));

    main_window(T, &vec, 0);

    vector_destroy(&vec);
    trietree_free(T);

    return 0;
}
