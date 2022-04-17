#include "test_common.h"
#include <sgc/fs_vector.h>

#define VECTOR_MAX 512

SGC_INIT_FS_VECTOR(int, VECTOR_MAX, vector)

void vector_pop_front(vector* v) {
    vector_erase(v, 0);
}

void test_fs_vector_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(vector, TEST_RANDOM_ACCESS_ITERATOR);
}

SGC_INIT_FS_VECTOR(oint, VECTOR_MAX, ovector)

void ovector_pop_front(ovector* v) {
    ovector_erase(v, 0);
}

void test_fs_vector_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(ovector, TEST_RANDOM_ACCESS_ITERATOR);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_vector_insert_erase_combinations);
    RUN_TEST(test_fs_vector_insert_erase_combinations_observed);
    return UNITY_END();
}
