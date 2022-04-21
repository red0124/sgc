#include "test_common.h"
#include <sgc/vector.h>
#include <unistd.h>

SGC_INIT_VECTOR(int, vector)

void vector_pop_front(vector* v) {
    vector_erase(v, 0);
}

void test_vector_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(vector, TEST_RANDOM_ACCESS_ITERATOR);
}

SGC_INIT_VECTOR(oint, ovector)

void ovector_pop_front(ovector* v) {
    ovector_erase(v, 0);
}

void test_vector_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(ovector, TEST_RANDOM_ACCESS_ITERATOR);
    ASSERT_ALLOCATION_COUNT
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_vector_insert_erase_combinations);
    RUN_TEST(test_vector_insert_erase_combinations_observed);

    disable_allocation();
    RUN_TEST(test_vector_insert_erase_combinations);
    RUN_TEST(test_vector_insert_erase_combinations_observed);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_vector_insert_erase_combinations);
    RUN_TEST(test_vector_insert_erase_combinations_observed);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_vector_insert_erase_combinations);
    RUN_TEST(test_vector_insert_erase_combinations_observed);
    return UNITY_END();
}
