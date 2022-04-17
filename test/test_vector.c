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
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_vector_insert_erase_combinations);
    RUN_TEST(test_vector_insert_erase_combinations_observed);
    return UNITY_END();
}
