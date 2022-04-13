#include <sgc/vector.h>
#include <stdio.h>

SGC_INIT(VECTOR, int, vec)

int main(void) {
    vec v;
    vec_init(&v);

    for (size_t i = 0; i < 5; ++i) {
        vec_push_back(&v, i);
    }

    printf("size: %zu\n", vec_size(&v));

    for_each(i IN v AS vec) {
        printf("%d \n", *i);
    }

    vec_free(&v);
    return 0;
}
