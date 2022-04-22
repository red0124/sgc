#include <sgc/vector.h>
#include <stdio.h>

// vec <=> vector<int>
SGC_INIT(VECTOR, int, vec)

int main(void) {
    vec v;
    vec_init(&v);

    vec_push_back(&v, 1);
    vec_push_back(&v, 5);

    *vec_at(&v, 0) = 2;

    for_each(i IN v AS vec) {
        printf("%d ", *i);
    }

    vec_free(&v);
    return 0;
}
