#include "test_common.h"
#include <sgc/vector.h>
#include <unistd.h>

SGC_INIT_VECTOR(int, vector)

void vector_pop_front(vector* v) {
    vector_erase(v, 0);
}

void test_vector_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(vector);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_vector_insert_erase_combinations);
    return UNITY_END();
}
