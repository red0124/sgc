#include "test_common.h"
#include <sgc/static_vector.h>

#define VECTOR_MAX 512

SGC_INIT_SVECTOR(int, VECTOR_MAX, vector)

void vector_pop_front(vector* v) {
    vector_erase(v, 0);
}

void test_static_vector_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(vector);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_static_vector_insert_erase_combinations);
    return UNITY_END();
}
