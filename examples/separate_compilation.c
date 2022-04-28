#include "sp_headers.h"
#include <stdio.h>

int main() {
    vec v;
    vec_init(&v);

    vec_push_back(&v, 3);
    vec_push_back(&v, 1);
    vec_push_back(&v, 2);

    printf("vec:\n");
    for_each(i IN v AS vec) {
        printf("%d\n", *i);
    }

    vec_qsort_default(&v);

    printf("sorted vec:\n");
    for_each(i IN v AS vec) {
        printf("%d\n", *i);
    }

    vec_free(&v);
    return 0;
}
