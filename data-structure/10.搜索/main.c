#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search.h"
#include "student.h"
#include "vector.h"

int name_comp(const void *a, const void *b) {
    return strcmp(((struct Student *)a)->name, ((struct Student *)b)->name);
}

int id_comp(const void *a, const void *b) {
    return ((struct Student *)a)->id - ((struct Student *)b)->id;
}

int birthday_comp(const void *a, const void *b) {
    if (((struct Student *)a)->birthday.year == ((struct Student *)b)->birthday.year) {
        if (((struct Student *)a)->birthday.month == ((struct Student *)b)->birthday.month) {
            return ((struct Student *)a)->birthday.day - ((struct Student *)b)->birthday.day;
        } else {
            return ((struct Student *)a)->birthday.month == ((struct Student *)b)->birthday.month;
        }
    } else {
        return ((struct Student *)a)->birthday.year - ((struct Student *)b)->birthday.year;
    }
}

int main() {
    struct Vector students;
    vector_init(&students, 10);

    vector_push_back(
        &students, (struct Student){
                       .id = 1, .name = "Tom", .birthday = {.year = 1999, .month = 2, .day = 10}});
    vector_push_back(
        &students, (struct Student){
                       .id = 2, .name = "Jack", .birthday = {.year = 2000, .month = 3, .day = 20}});
    vector_push_back(
        &students, (struct Student){
                       .id = 3, .name = "Mike", .birthday = {.year = 1999, .month = 8, .day = 7}});

    sort(&students, name_comp);

    int m = search(&students, &(struct Student){.name = "Mike"}, name_comp);
    int t = bin_search(&students, &(struct Student){.name = "Tom"}, name_comp);

    vector_destroy(&students);

    return 0;
}
